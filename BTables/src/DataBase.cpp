#include "DataBase.h"

bool BTables::DataBase::connect()
{
    if (m_db.isOpen())
    {
        return true;
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("tables.db");
    bool stateOfOpen = m_db.open();
    QSqlQuery* query = new QSqlQuery(m_db);
    query->exec("CREATE TABLE IF NOT EXISTS tables(id INTEGER PRIMARY KEY, toTable TEXT, first TEXT, second TEXT)");
    return stateOfOpen;
}

QMap<QString, QString> BTables::DataBase::getDataOfTable(const QString tableName)
{
    QMap<QString, QString> tableData;
    if (hasTable(tableName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("SELECT * FROM tables WHERE toTable = :toTable");
        query->bindValue(":toTable", tableName);
        query->exec();
        while (query->next())
        {
            tableData.insert(query->value("first").toString(), query->value("second").toString());
        }
        return tableData;
    }
    else
    {
        return QMap<QString, QString>();
    }
}

void BTables::DataBase::renameTable(const QString oldName, const QString newName)
{
    if (hasTable(oldName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("UPDATE tables SET toTable = :newTableName WHERE toTable = :oldTableName");
        query->bindValue(":newTableName", newName);
        query->bindValue(":oldTableName", oldName);
        query->exec();
    }
}

void BTables::DataBase::addNewField(const QString tableName, QString value1, QString value2)
{
    if (hasTable(tableName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("INSERT INTO tables(NULL, :tableName, :first, :second)");
        query->bindValue(":tableName", tableName);
        query->bindValue(":first", value1);
        query->bindValue(":second", value2);
        query->exec();
    }
}

void BTables::DataBase::updateField(const QString tableName, QString value1, QString value2)
{
    if (hasTable(tableName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("UPDATE tables SET first = :first, second = :second WHERE toTable = :toTable");
        query->bindValue(":toTable", tableName);
        query->bindValue(":first", value1);
        query->bindValue(":second", value2);
        query->exec();
    }
}

void BTables::DataBase::removeField(const QString tableName, QString value1, QString value2)
{
    if (hasTable(tableName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("DELETE FROM tables WHERE toTable = :toTable AND first = :first AND second = :second");
        query->bindValue(":toTable", tableName);
        query->bindValue(":first", value1);
        query->bindValue(":second", value2);
        query->exec();
    }
}

void BTables::DataBase::removeTable(const QString tableName)
{
    if (hasTable(tableName))
    {
        QSqlQuery* query = new QSqlQuery(m_db);
        query->prepare("DELETE FROM tables WHERE toTable = :toTable");
        query->bindValue(":toTable", tableName);
        query->exec();
    }
}

BTables::DataBase::~DataBase()
{
    m_db.close();
}

bool BTables::DataBase::hasTable(const QString tableName)
{
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("SELECT * FROM tables WHERE toTable = :toTable");
    query->bindValue(":toTable", tableName);
    query->exec();
    return query->next();
}
