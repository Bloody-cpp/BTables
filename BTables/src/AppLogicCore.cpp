#include "AppLogicCore.h"

BTables::AppLogicCore::AppLogicCore(QObject* parent) : QObject(parent)
{
	QObject::connect(
		m_mainWindow.m_mainForm.availableTables,
		SIGNAL(itemClicked(QListWidgetItem*)),
		this,
		SLOT(onSelectTable(QListWidgetItem*))
	);

	QObject::connect(
		&m_mainWindow.m_createTableDialog,
		&CreateTableDialog::newTable,
		this,
		&onCreateNewTable(const BTables::CreateTableDialog::Data)
	);

	QObject::connect(
		m_mainWindow.m_mainForm.closeButton,
		SIGNAL(clicked()),
		this,
		SLOT(onExit())
	);

	m_debug = new DebugWindow();
	m_database = new DataBase(m_debug, this);
	m_debug->show();
	m_mainWindow.show();
	m_database->connect();
}

BTables::AppLogicCore::~AppLogicCore() {}

void BTables::AppLogicCore::updateTablesList()
{
	m_mainWindow.m_mainForm.availableTables->clear();
	m_mainWindow.m_mainForm.availableTables->addItems(m_database->tables());
}

void BTables::AppLogicCore::onCreateNewTable(const CreateTableDialog::Data data)
{
	m_database->createTable(data.m_tableName, data.m_numberColumns);
	updateTablesList();
	m_debug->infoMessage("New table was create");
}

void BTables::AppLogicCore::onExit()
{
	m_database->~DataBase();
	QCoreApplication::quit();
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