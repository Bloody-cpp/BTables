#include "MainWindow.h"

BTables::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	m_db = new DataBase(this);
	m_mainForm.setupUi(this);

	connect(m_createTableDialog.getUI()->confirmButton, SIGNAL(clicked()), this, SLOT(on_createTableConfirm()));
}
void BTables::MainWindow::updateTablesList()
{
	m_mainForm.availableTables->clear();
	m_mainForm.availableTables->addItems(m_db->tables());
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
void BTables::MainWindow::on_availableTables_itemClicked(QListWidgetItem* item)
{
	m_mainForm.currentTable->clear();
	QVector<QVector<QString>> dataOfTable = m_db->getDataOfTable(item->text());
	if (dataOfTable.size() == 0)
	{
		warnMessage("Selected table was empty");
		return;
	}
	for (size_t y = 0; y < dataOfTable.size(); y++)
	{
		for (size_t x = 0; x < dataOfTable[y].size(); x++)
		{
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setData(Qt::DisplayRole, dataOfTable[y][x]);
			m_mainForm.currentTable->setItem(y, x, item);
		}
	}
	infoMessage("Succesful load table");
}
void BTables::MainWindow::on_createTableConfirm()
{
	if (m_createTableDialog.checkEmpty())
	{
		m_db->createTable(m_createTableDialog.getTableName(), m_createTableDialog.getNumberColumns());
		updateTablesList();
		m_createTableDialog.done(0);
		infoMessage("New table was create");
	}
	warnMessage("Name field table is empty");
}
void BTables::MainWindow::on_createTableButton_clicked()
{
	m_createTableDialog.exec();
}
void BTables::MainWindow::on_closeButton_clicked()
{
	m_db->~DataBase();
	QCoreApplication::quit();
}