#pragma once
#include <Include.h>
#include <Debug.h>
#include <DataParser.h>

namespace BTables
{
	class DataBase : public QObject
	{
		Q_OBJECT

		QSqlDatabase m_db;
	public:
		explicit DataBase(QObject* parent = nullptr);
		void connect();
		QStringList tables();
		TableData getParseTableData(const QString tableName);
		TableRow getTableRow(const QString tableName, const TableY coord);
		QString getSerializeTableData(const QString tableName);
		int getColumns(const QString tableName);
		void createTable(const QString tableName, const short numberColumns);
		void renameTable(const QString oldName, const QString newName);
		void addNewField(const QString tableName, TableRow rowData);
		void updateField(const QString tableName, TableRow rowData);
		void updateAt(const QString tableName, int x, int y, const QString value);
		void setColumns(const QString tableName, const short numbeColumns);
		void removeField(const QString tableName, const size_t row);
		void removeTable(const QString tableName);
		void updateDataOfTable(const QString tableName, const QString newData);
		~DataBase();
	private:
		size_t searchIndexOfRow(TableData decode, TableRow row);
		bool hasTable(const QString tableName);
		bool correctColumnsNumber(TableRow rowData, QString tableName);
	};
}