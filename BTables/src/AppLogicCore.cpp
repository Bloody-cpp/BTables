#include "AppLogicCore.h"

BTables::AppLogicCore::AppLogicCore(QObject* parent) : QObject(parent)
{
	QObject::connect(
		m_mainWindow.m_mainForm.availableTables,
		SIGNAL(itemClicked(QListWidgetItem*)),
		this,
		SLOT(onSelectTable(QListWidgetItem*))
	);
	m_debug = new DebugWindow();
	m_database = new DataBase(m_debug, this);	
	m_debug->show();
	m_mainWindow.show();
}

BTables::AppLogicCore::~AppLogicCore() {}

void BTables::AppLogicCore::initializeListTables()
{
	m_mainWindow.m_mainForm.availableTables->addItems(m_database->tables());
}

void BTables::AppLogicCore::onSelectTable(QListWidgetItem* clickedItem)
{
	m_mainWindow.m_mainForm.currentTable->clear();
	QVector<QVector<QString>> dataOfTable = m_database->getDataOfTable(clickedItem->text());
	if (dataOfTable.size() == 0)
	{
		m_debug->warnMessage("Selected table was empty");
		return;
	}
	for (size_t y = 0; y < dataOfTable.size(); y++)
	{
		for (size_t x = 0; x < dataOfTable[y].size(); x++)
		{
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setData(Qt::DisplayRole, dataOfTable[y][x]);
			m_mainWindow.m_mainForm.currentTable->setItem(y, x, item);
		}
	}
}