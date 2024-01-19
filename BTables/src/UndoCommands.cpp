#include "UndoCommands.h"

//DeleteTableCommand
BTables::DeleteTableCommand::DeleteTableCommand(MainWindow* mainWindow, const QString tableName) : m_mainWindow(mainWindow), m_tableName(tableName) 
{
	m_columns = m_mainWindow->m_db->getColumns(m_tableName);
	m_index = m_mainWindow->m_mainForm.availableTables->currentRow();
	m_serializeData = m_mainWindow->m_db->getSerializeTableData(m_tableName);
}
void BTables::DeleteTableCommand::undo()
{
	m_mainWindow->m_db->createTable(m_tableName, m_columns);
	m_mainWindow->m_db->updateDataOfTable(m_tableName, m_serializeData);
	m_mainWindow->m_mainForm.availableTables->insertItem(m_index, m_tableName);
	m_mainWindow->loadTable(m_tableName);
	m_mainWindow->m_mainForm.availableTables->setCurrentRow(m_index);
}
void BTables::DeleteTableCommand::redo()
{
	m_mainWindow->m_db->removeTable(m_tableName);
	m_mainWindow->updateTablesList();
	if (m_mainWindow->isAnyTableExists())
	{
		m_mainWindow->loadFirstExistsTable();
	}
	else
	{
		m_mainWindow->m_mainForm.currentTable->setRowCount(0);
		m_mainWindow->m_mainForm.currentTable->setColumnCount(0);
		m_mainWindow->m_mainForm.currentTable->clear();
	}
}

//DeleteFieldCommand
BTables::DeleteFieldCommand::DeleteFieldCommand(MainWindow* mainWindow, const TableY coord)
{
	m_mainWindow = mainWindow;
	m_coord = coord;
	m_tableName = m_mainWindow->getCurrentTableName();
	m_data = m_mainWindow->m_db->getTableRow(m_tableName, coord);
}
void BTables::DeleteFieldCommand::undo()
{
	m_mainWindow->m_db->insertTableRow(m_tableName, m_data, m_coord);
	m_mainWindow->loadTable(m_tableName);
}
void BTables::DeleteFieldCommand::redo()
{
	m_mainWindow->m_db->removeField(m_tableName, m_coord);
	m_mainWindow->loadTable(m_tableName);
}

//EditCellCommand
BTables::EditCellCommand::EditCellCommand(MainWindow* mainWindow, const TableCoord coord, const QString newData, const QString oldData) : m_coord(coord)
{
	m_mainWindow = mainWindow;
	m_newData = newData;
	m_oldData = oldData;
	m_tableName = m_mainWindow->getCurrentTableName();
}
void BTables::EditCellCommand::undo()
{
	m_mainWindow->m_db->updateAt(m_tableName, m_coord.m_x, m_coord.m_y, m_oldData);
	m_mainWindow->loadTable(m_tableName);
}
void BTables::EditCellCommand::redo()
{
	m_mainWindow->m_db->updateAt(m_tableName, m_coord.m_x, m_coord.m_y, m_newData);
	m_mainWindow->loadTable(m_tableName);
}

//FieldCreateCommand
BTables::FieldCreateCommand::FieldCreateCommand(MainWindow* mainWindow)
{
	m_mainWindow = mainWindow;
	m_tableName = m_mainWindow->getCurrentTableName();
}
void BTables::FieldCreateCommand::undo()
{
	m_mainWindow->m_db->removeField(m_tableName, m_mainWindow->m_mainForm.currentTable->rowCount() - 1);
	m_mainWindow->loadTable(m_tableName);
}
void BTables::FieldCreateCommand::redo()
{
	const size_t columnsCount = m_mainWindow->m_db->getColumns(m_tableName);
	TableRow row(columnsCount, "");
	m_mainWindow->m_db->addNewField(m_tableName, row);
	m_mainWindow->loadTable(m_tableName);
}
