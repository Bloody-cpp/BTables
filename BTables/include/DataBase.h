#pragma once
#include <DefaultInclude.h>
#include <DebugWindow.h>

namespace BTables
{
	class DataBase : public QObject
	{
		Q_OBJECT

		Debugger m_debug;
		QSqlDatabase m_db;
	public:
		explicit DataBase(Debugger debug, QObject* parent = nullptr);
		void connect();
		QStringList tables();
		QVector<QVector<QString>> getDataOfTable(const QString tableName);
		void renameTable(const QString oldName, const QString newName);
		void addNewField(const QString tableName, QVector<QString> fieldData);
		void updateField(const QString tableName, QVector<QString> fieldData);
		void removeField(const QString tableName, QVector<QString> fieldData);
		void removeTable(const QString tableName);
		~DataBase();
	private:
		QString getDataFromTable(const QString tableName);
		void updateDataOfTable(const QString tableName, const QString newData);
		size_t searchIndexOfRow(QVector<QVector<QString>> decode, QVector<QString> row);
		QString serializeRow(QVector<QString> rowData);
		QString serializeData(QVector<QVector<QString>> data);
		QVector<QVector<QString>> parseData(const QString dataString);
		bool hasTable(const QString tableName);
	};
}