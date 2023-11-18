#pragma once
#include <DefaultInclude.h>

namespace BTables
{
	class DataBase : public QObject
	{
		Q_OBJECT

		QSqlDatabase m_db;
	public:
		explicit DataBase(QObject* parent) : QObject(parent) {}
		bool connect();
		QMap<QString, QString> getDataOfTable(const QString tableName);
		void renameTable(const QString oldName, const QString newName);
		void addNewField(const QString tableName, QString value1, QString value2);
		void updateField(const QString tableName, QString value1, QString value2);
		void removeField(const QString tableName, QString value1, QString value2);
		void removeTable(const QString tableName);
		~DataBase();
	private:
		bool hasTable(const QString tableName);
	};
}