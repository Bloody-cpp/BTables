#include "MainWindow.h"

BTables::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

	//Initialize
	m_debugWindow = new DebugWindow();
	setupDebugWindow(m_debugWindow);
	m_debugWindow->show();

	m_db = new DataBase(this);
	m_db->connect();

	//Connecting all slots
	connect(m_createTableDialog.getUI()->confirmButton, SIGNAL(clicked()), this, SLOT(on_createTableConfirm()));
	connect(m_setColumnsDialog.getUI()->confirmButton, SIGNAL(clicked()), this, SLOT(on_setColumnsConfirm()));

	m_mainForm.setupUi(this);
	updateTablesList();
	QStringList tables = m_db->tables();
	if (!tables.isEmpty())
	{
		m_mainForm.availableTables->setCurrentRow(0);
		loadTable(tables[0]);
	}
}
QString BTables::MainWindow::getCurrentTableName()
{
	return m_mainForm.availableTables->currentItem()->text();
}
void BTables::MainWindow::loadTable(const QString tableName)
{
	m_mainForm.currentTable->blockSignals(true);
	QVector<TableRow> dataOfTable = m_db->getDataOfTable(tableName);
	m_mainForm.currentTable->setRowCount(dataOfTable.size());
	m_mainForm.currentTable->setColumnCount(m_db->getColumns(tableName));
	for (size_t rows = 0; rows < dataOfTable.size(); rows++)
	{
		for (size_t unit = 0; unit < dataOfTable[rows].size(); unit++)
		{
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setData(Qt::EditRole, dataOfTable[rows][unit]);
			m_mainForm.currentTable->setItem(rows, unit, item);
		}
	}
	infoMessage("Succesful load table");
	m_mainForm.currentTable->blockSignals(false);
}
void BTables::MainWindow::updateTablesList()
{
	m_mainForm.availableTables->clear();
	m_mainForm.availableTables->addItems(m_db->tables());
}
bool BTables::MainWindow::isAnyTableExists()
{
	return m_db->tables().size() != 0;
}
void BTables::MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton &&
		event->modifiers() == Qt::NoModifier)
	{
		m_dragPosition = event->globalPos();
		return;
	}
	QWidget::mousePressEvent(event);
}
void BTables::MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (m_dragPosition == kInvalidPoint)
		return QWidget::mouseMoveEvent(event);

	const QPoint delta = event->globalPos() - m_dragPosition;
	move(pos() + delta);
	m_dragPosition = event->globalPos();
}
void BTables::MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
	m_dragPosition = kInvalidPoint;
	QWidget::mouseReleaseEvent(event);
}
void BTables::MainWindow::on_setColumnsConfirm()
{
	m_db->setColumns(getCurrentTableName(), m_setColumnsDialog.getNumberColumns());
	m_setColumnsDialog.done(0);
	loadTable(getCurrentTableName());
}
void BTables::MainWindow::on_currentTable_itemChanged(QTableWidgetItem* item)
{
	infoMessage("Changes at: x:" + QString::number(item->column()) + " y: " + QString::number(item->row()));
	infoMessage("Value: " + item->text());
	m_db->updateAt(getCurrentTableName(), item->column(), item->row(), item->text());
}
void BTables::MainWindow::on_availableTables_itemClicked(QListWidgetItem* item)
{
	m_mainForm.currentTable->clear();
	loadTable(item->text());
}
void BTables::MainWindow::on_createTableConfirm()
{
	if (m_createTableDialog.checkEmpty())
	{
		m_db->createTable(m_createTableDialog.getTableName(), m_createTableDialog.getNumberColumns());
		m_createTableDialog.done(0);
		updateTablesList();
		if (m_db->tables().size() == 1)
		{
			m_mainForm.availableTables->setCurrentRow(0);
			loadTable(m_createTableDialog.getTableName());
		}
		infoMessage("New table was create");
		return;
	}
	warnMessage("Name field table is empty");
}
void BTables::MainWindow::on_createTableButton_clicked()
{
	m_createTableDialog.getUI()->tableName->setText("");
	m_createTableDialog.exec();
}
void BTables::MainWindow::on_setColumnsButton_clicked()
{
	if (isAnyTableExists())
	{
		m_setColumnsDialog.getUI()->numberOfColumns->setValue(m_db->getColumns(getCurrentTableName()));
		m_setColumnsDialog.exec();
	}
}
void BTables::MainWindow::on_addFieldButton_clicked()
{
	if (isAnyTableExists())
	{
		infoMessage("Start of creating new field");
		TableRow row;
		const size_t columnsCount = m_db->getColumns(getCurrentTableName());
		m_mainForm.currentTable->blockSignals(true);
		m_mainForm.currentTable->insertRow(m_mainForm.currentTable->rowCount());
		for (size_t x = 0; x < columnsCount; x++)
		{
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setData(Qt::EditRole, "");
			row.push_back("");
			m_mainForm.currentTable->setItem(m_mainForm.currentTable->rowCount() - 1, x, item);
		}
		m_mainForm.currentTable->blockSignals(false);
		m_db->addNewField(getCurrentTableName(), row);
	}
}
void BTables::MainWindow::on_closeButton_clicked()
{
	m_db->~DataBase();
	QCoreApplication::quit();
}