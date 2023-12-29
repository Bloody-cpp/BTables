#include "DataBase.h"

BTables::DataBase::DataBase(QObject* parent) : QObject(parent) {}
void BTables::DataBase::connect()
{
    if (m_db.isOpen())
    {
        warnMessage("Double call db.connect");
        return;
    }
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("tables.db");
    if (m_db.open())
    {
        infoMessage("Succesful connected to database");
    }
    else
    {
        fatalMessage("Can`t connect to database");
    }
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("CREATE TABLE IF NOT EXISTS tables(id INTEGER PRIMARY KEY, tableName TEXT UNICAL, data TEXT, columns INT)");
    sqlMessage(query, "Create 'tables'");
}
QStringList BTables::DataBase::tables()
{
    QStringList list;
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("SELECT * FROM tables");
    sqlMessage(query, "Call db.tables");
    while (query->next())
    {
        list.push_back(query->value("tableName").toString());
    }
    return list;
}
QVector<QVector<QString>> BTables::DataBase::getDataOfTable(const QString tableName)
{
    if (hasTable(tableName))
    {
        return parseData(getDataFromTable(tableName));
    }
    else
    {
        return QVector<QVector<QString>>();
    }
}
int BTables::DataBase::getColumns(const QString tableName)
{
    if (hasTable(tableName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("SELECT columns FROM tables WHERE tableName = :tableName");
        query->bindValue(":tableName", tableName);
        sqlMessage(query, "Call db.getColumns");
        query->next();
        return query->value(0).toInt();
    }
    return 0;
}
void BTables::DataBase::createTable(const QString tableName, short numberColumns)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("INSERT INTO tables(tableName, data, columns) VALUES(:tableName, :data, :columns)");
    query->bindValue(":tableName", tableName);
    query->bindValue(":columns", numberColumns);
    query->bindValue(":data", serializeRow(TableRow(numberColumns, "")));
    sqlMessage(query, "Call db.createTable");
}
void BTables::DataBase::renameTable(const QString oldName, const QString newName)
{
    if (hasTable(oldName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("UPDATE tables SET tableName = :newTableName WHERE tableName = :oldTableName");
        query->bindValue(":newTableName", newName);
        query->bindValue(":oldTableName", oldName);
        sqlMessage(query, "Call db.renameTable");
    }
}
void BTables::DataBase::addNewField(const QString tableName, QVector<QString> fieldData)
{
    if (hasTable(tableName) && correctColumnsNumber(fieldData, tableName))
    {
        QString newData = getDataFromTable(tableName) + serializeRow(fieldData);
        updateDataOfTable(tableName, newData);
    }
}
void BTables::DataBase::updateField(const QString tableName, QVector<QString> fieldData)
{
    if (hasTable(tableName) && correctColumnsNumber(fieldData, tableName))
    {
        QVector<QVector<QString>> decode = parseData(getDataFromTable(tableName));
        QVector<QString>& needRow = decode[searchIndexOfRow(decode, fieldData)];
        for (size_t x = 0; x < fieldData.size(); x++)
        {
            if (fieldData[x].size() != 0)
            {
                needRow[x] = fieldData[x];
            }
        }
        QString serializedResult = serializeData(decode);
        infoMessage("db.updateField.serialized: " + serializedResult);
        updateDataOfTable(tableName, serializedResult);
    }
}
void BTables::DataBase::removeField(const QString tableName, QVector<QString> fieldData)
{
    if (hasTable(tableName) && correctColumnsNumber(fieldData, tableName))
    {
        QVector<QVector<QString>> decode = parseData(getDataFromTable(tableName));
        decode.erase(decode.begin() + searchIndexOfRow(decode, fieldData));
        QString serializedResult = serializeData(decode);
        infoMessage("db.removeField.serialized: " + serializedResult);
        updateDataOfTable(tableName, serializedResult);
    }
}
void BTables::DataBase::removeTable(const QString tableName)
{
    if (hasTable(tableName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("DELETE FROM tables WHERE tableName = :tableName");
        query->bindValue(":tableName", tableName);
        sqlMessage(query, "db.removeTable");
    }
}
BTables::DataBase::~DataBase()
{
    m_db.close();
}
void BTables::DataBase::updateAt(const QString tableName, int x, int y, const QString value)
{
    if (hasTable(tableName))
    {
        QVector<TableRow> decode = parseData(getDataFromTable(tableName));
        infoMessage("value is: " + value);
        for (size_t x = 0; x < decode.size(); x++)
        {

        }
        infoMessage("rows: " + QString::number(decode.size()));
        if (decode.size() != 0)
        {
            infoMessage("units: " + QString::number(decode[0].size()));
        }
        //decode[x][y] = value;
        //QString serializedResult = serializeData(decode);
        //infoMessage("db.updateAt.serialized: " + serializedResult);
        //updateDataOfTable(tableName, serializedResult);
    }
}
QString BTables::DataBase::getDataFromTable(const QString tableName)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("SELECT data FROM tables WHERE tableName = :tableName");
    query->bindValue(":tableName", tableName);
    sqlMessage(query, "Call db.getDataFromTable");
    query->next();
    QString result = query->value(0).toString();
    infoMessage("Result of call: " + result);
    return result;
}
void BTables::DataBase::updateDataOfTable(const QString tableName, const QString newData)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("UPDATE tables SET data = :newData WHERE tableName = :tableName");
    query->bindValue(":newData", newData);
    query->bindValue(":tableName", tableName);
    sqlMessage(query, "Call db.updateDataOfTable");
}
size_t BTables::DataBase::searchIndexOfRow(QVector<QVector<QString>> decode, QVector<QString> row)
{
    for (size_t x = 0; x < decode.size(); x++)
    {
        if (decode[x] == row)
        {
            return x;
        }
    }
    errorMessage("Can`t search index of row");
    return SIZE_MAX;
}
QString BTables::DataBase::serializeRow(QVector<QString> rowData)
{
    return rowData.join('.');
}
QString BTables::DataBase::serializeData(QVector<BTables::TableRow> data)
{
    QVector<QString> bufferForPackRows;
    for (size_t x = 0; x < data.size(); x++)
    {
        bufferForPackRows.push_back(data[x].join('.'));
    }
    return bufferForPackRows.join(';');
}
QVector<BTables::TableRow> BTables::DataBase::parseData(const QString dataString)
{
    QVector<BTables::TableRow> resultParse;
    BTables::TableRow rows = dataString.split(';');
    for (size_t x = 0; x < rows.size(); x++)
    {
        resultParse.push_back(rows[x].split('.'));
    }
    return resultParse;
}
bool BTables::DataBase::hasTable(const QString tableName)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("SELECT * FROM tables WHERE tableName = :tableName");
    query->bindValue(":tableName", tableName);
    query->exec();
    if (!query->next())
    {
        warnMessage("Table don`t create");
        return 0;
    }
    return 1;
}
bool BTables::DataBase::correctColumnsNumber(QVector<QString> fieldData, QString tableName)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("SELECT columns FROM tables WHERE tableName = :tableName");
    query->bindValue(":tableName", tableName);
    query->exec();
    query->next();
    if (fieldData.size() == query->value(0).toInt())
    {
        return true;
    }
    return false;
}