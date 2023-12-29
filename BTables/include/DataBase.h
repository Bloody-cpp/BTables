#pragma once
#include <Include.h>
#include <Debug.h>

#define EMPTYFIELD_TEXT "Empty"

namespace BTables
{
	using TableRow = QVector<QString>;

	class DataBase : public QObject
	{
		Q_OBJECT

		QSqlDatabase m_db;
	public:
		explicit DataBase(QObject* parent = nullptr);
		void connect();
		QStringList tables();
		QVector<QVector<QString>> getDataOfTable(const QString tableName);
		int getColumns(const QString tableName);
		void createTable(const QString tableName, short numberColumns);
		void renameTable(const QString oldName, const QString newName);
		void addNewField(const QString tableName, QVector<QString> fieldData);
		void updateField(const QString tableName, QVector<QString> fieldData);
		void updateAt(const QString tableName, int x, int y, const QString value);
		void removeField(const QString tableName, QVector<QString> fieldData);
		void removeTable(const QString tableName);
		QString serializeData(QVector<QVector<QString>> data);
		void updateDataOfTable(const QString tableName, const QString newData);
		~DataBase();
	private:
		QString getDataFromTable(const QString tableName);
		size_t searchIndexOfRow(QVector<QVector<QString>> decode, QVector<QString> row);
		QString serializeRow(QVector<QString> rowData);
		QVector<QVector<QString>> parseData(const QString dataString);
		bool hasTable(const QString tableName);
		bool correctColumnsNumber(QVector<QString> fieldData, QString tableName);
	};
}