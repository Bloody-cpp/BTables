#include "UndoCommands.h"

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
