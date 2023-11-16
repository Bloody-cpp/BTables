#pragma once
#include <defaultInclude.h>

class DataBase : public QObject
{
	Q_OBJECT

	QSqlDatabase* m_db;
public:
	explicit DataBase(QObject* parent) : QObject(parent) {}
	bool connect();
	QVector<QString> getTablesName();
	QMap<QString, QString> getDataOfTable(const QString tableName);
	void addNewField(const QString tableName, QString value1, QString value2);
	void updateField(const QString tableName, QString value1, QString value2);
	void removeField(const QString tableName, QString value1, QString value2);
	void removeTable(const QString tableName);
	~DataBase();
};

