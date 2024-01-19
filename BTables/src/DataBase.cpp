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
    query->prepare("SELECT tableName FROM tables");
    query->exec();
    while (query->next())
    {
        list.push_back(query->value(0).toString());
    }
    return list;
}
BTables::TableData BTables::DataBase::getParseTableData(const QString tableName)
{
    if (hasTable(tableName))
    {
        return parseData(getSerializeTableData(tableName));
    }
    else
    {
        return TableData();
    }
}
BTables::TableRow BTables::DataBase::getTableRow(const QString tableName, const TableY coord)
{
    if (hasTable(tableName))
    {
        TableData tableData = getParseTableData(tableName);
        if (tableData.isEmpty() || tableData.size() - 1 < coord)
        {
            return TableRow();
        }
        return tableData[coord];
    }
    return TableRow();
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
void BTables::DataBase::insertTableRow(const QString tableName, TableRow row, TableY coord)
{
    if (hasTable(tableName))
    {
        TableData tableData = getParseTableData(tableName);
        if (tableData.isEmpty() || tableData.size() - 1 < coord)
        {
            return;
        }
        tableData.insert(tableData.begin() + coord, row);
        updateDataOfTable(tableName, serialize(tableData));
    }
}
void BTables::DataBase::createTable(const QString tableName, short numberColumns)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("INSERT INTO tables(tableName, data, columns) VALUES(:tableName, :data, :columns)");
    query->bindValue(":tableName", tableName);
    query->bindValue(":columns", numberColumns);
    query->bindValue(":data", addToSerialize("", TableRow(numberColumns, "")));
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
void BTables::DataBase::addNewField(const QString tableName, TableRow rowData)
{
    if (hasTable(tableName) && correctColumnsNumber(rowData, tableName))
    {
        QString newData = addToSerialize(getSerializeTableData(tableName), rowData);
        updateDataOfTable(tableName, newData);
    }
}
void BTables::DataBase::setColumns(const QString tableName, const short newNumberColumns)
{
    if (hasTable(tableName))
    {
        TableData dataOfTable = parseData(getSerializeTableData(tableName));
        const short currentNumberColumns = getColumns(tableName);
        if (currentNumberColumns == newNumberColumns)
        {
            return;
        }
        if (currentNumberColumns < newNumberColumns)
        {
            for (size_t x = 0; x < dataOfTable.size(); x++)
            {
                infoMessage("+ Length of row old: " + QString::number(dataOfTable[x].size()));
                for (size_t y = 0; y < newNumberColumns - currentNumberColumns; y++)
                {
                    dataOfTable[x].push_back("");
                }
                infoMessage("+ Length of row: " + QString::number(dataOfTable[x].size()));
            }
        }
        else
        {
            for (size_t x = 0; x < dataOfTable.size(); x++)
            {
                infoMessage("- Length of row old: " + QString::number(dataOfTable[x].size()));
                auto beginIter = dataOfTable[x].begin() + (dataOfTable[x].size() - (currentNumberColumns - newNumberColumns));
                dataOfTable[x].erase(beginIter, dataOfTable[x].end());
                infoMessage("- Length of row: " + QString::number(dataOfTable[x].size()));
            }
        }
        
        updateDataOfTable(tableName, serialize(dataOfTable));
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("UPDATE tables SET columns = :newColumns WHERE tableName = :tableName");
        query->bindValue(":newColumns", newNumberColumns);
        query->bindValue(":tableName", tableName);
        sqlMessage(query, "Call db.setColumns");
    }
}
void BTables::DataBase::removeField(const QString tableName, const size_t yCoord)
{
    if (hasTable(tableName))
    {
        TableData decode = getParseTableData(tableName);
        decode.erase(decode.begin() + yCoord);
        QString serializedResult = serialize(decode);
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
void BTables::DataBase::updateAt(const QString tableName, int x, int y, const QString value)
{
    if (hasTable(tableName))
    {
        TableData decode = parseData(getSerializeTableData(tableName));
        decode[y][x] = value;
        QString serializedResult = serialize(decode);
        infoMessage("db.updateAt.serialized: " + serializedResult);
        updateDataOfTable(tableName, serializedResult);
    }
}
QString BTables::DataBase::getSerializeTableData(const QString tableName)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("SELECT data FROM tables WHERE tableName = :tableName");
    query->bindValue(":tableName", tableName);
    sqlMessage(query, "Call db.getDataFromTable");
    query->next();
    return query->value(0).toString();
}
void BTables::DataBase::updateDataOfTable(const QString tableName, const QString newData)
{
    if (hasTable(tableName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("UPDATE tables SET data = :newData WHERE tableName = :tableName");
        query->bindValue(":newData", newData);
        query->bindValue(":tableName", tableName);
        sqlMessage(query, "Call db.updateDataOfTable");
    }
}
size_t BTables::DataBase::searchIndexOfRow(TableData decode, TableRow row)
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
bool BTables::DataBase::correctColumnsNumber(TableRow rowData, QString tableName)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("SELECT columns FROM tables WHERE tableName = :tableName");
    query->bindValue(":tableName", tableName);
    query->exec();
    query->next();
    if (rowData.size() == query->value(0).toInt())
    {
        return true;
    }
    return false;
}
BTables::DataBase::~DataBase()
{
    m_db.close();
}