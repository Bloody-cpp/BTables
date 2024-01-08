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
	loadFirstExistsTable();
}
QString BTables::MainWindow::getCurrentTableName()
{
	return m_mainForm.availableTables->currentItem()->text();
}
void BTables::MainWindow::loadTable(const QString tableName)
{
	m_mainForm.currentTable->blockSignals(true);
	m_mainForm.currentTable->clear();
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
void BTables::MainWindow::loadFirstExistsTable()
{
	QStringList tables = m_db->tables();
	if (!tables.isEmpty())
	{
		m_mainForm.availableTables->setCurrentRow(0);
		loadTable(tables[0]);
	}
}
void BTables::MainWindow::setOtherButtonsEnabled(const bool state)
{
	m_mainForm.addFieldButton->setEnabled(state);
	m_mainForm.createTableButton->setEnabled(state);
	m_mainForm.deleteTableButton->setEnabled(state);
	m_mainForm.removeFieldButton->setEnabled(state);
	m_mainForm.setColumnsButton->setEnabled(state);
}
QVector<BTables::TableRow> BTables::MainWindow::getCurrentTableState()
{
	if (isAnyTableExists())
	{
		QVector<BTables::TableRow> tableData;
		for (size_t y = 0; y < m_mainForm.currentTable->rowCount(); y++)
		{
			TableRow row;
			for (size_t x = 0; x < m_mainForm.currentTable->columnCount(); x++)
			{
				row.push_back(m_mainForm.currentTable->item(y, x)->text());
			}
			tableData.push_back(row);
		}
		return tableData;
	}

	return QVector<BTables::TableRow>();
}
size_t BTables::MainWindow::searchRowByFirstValue(const QVector<TableRow> rows, const QString fValue)
{
	for (size_t x = 0; x < rows.size(); x++)
	{
		if (rows[x][0] == fValue)
		{
			return x;
		}
	}
	return SIZE_MAX;
}
BTables::GuessResults BTables::MainWindow::makeResults(const QVector<TableRow> currentTableState)
{
	QVector<TableRow> startValues = m_db->getDataOfTable(getCurrentTableName());
	GuessResults results;
	for (size_t x = 0; x < startValues.size(); x++)
	{
		const size_t index = searchRowByFirstValue(currentTableState, startValues[x][0]);
		TableRow currentRow = currentTableState[index];
		bool wasErrorInRow = false;
		if (!startValues[x][0].isEmpty())
		{
			results.totalAnswers++;
			for (size_t y = 0; y < currentRow.size(); y++)
			{
				if (startValues[x][y] != currentRow[y])
				{
					wasErrorInRow = true;
					results.errorPlaces.push_back({ y, index });
				}
			}
			if (!wasErrorInRow)
			{
				results.trueAnswers++;
			}
		}
		else
		{
			for (size_t y = 0; y < startValues[x].size(); y++)
			{
				results.errorPlaces.push_back({ y, index });
			}
		}
	}
	return results;
}
void BTables::MainWindow::forbidChangeItem(QTableWidgetItem* item)
{
	item->setFlags(item->flags() & (~Qt::ItemIsEditable));
	item->setFlags(item->flags() & (~Qt::ItemIsSelectable));
}
void BTables::MainWindow::accessChangeItem(QTableWidgetItem* item)
{
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	item->setFlags(item->flags() | Qt::ItemIsSelectable);
}
bool BTables::MainWindow::eventFilter(QObject* object, QEvent* event)
{
	return false;
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
	if (m_windowState == MainMenu)
	{
		infoMessage("Changes at: x:" + QString::number(item->column()) + " y: " + QString::number(item->row()));
		infoMessage("Value: " + item->text());
		m_db->updateAt(getCurrentTableName(), item->column(), item->row(), item->text());
	}
}
void BTables::MainWindow::on_currentTable_itemClicked(QTableWidgetItem* item)
{
	
}
void BTables::MainWindow::on_availableTables_itemClicked(QListWidgetItem* item)
{
	if (m_windowState == MainMenu)
	{
		m_mainForm.currentTable->clear();
		loadTable(item->text());
	}
}
void BTables::MainWindow::on_createTableConfirm()
{
	if (m_createTableDialog.checkEmpty())
	{
		QStringList tables = m_db->tables();
		for (size_t x = 0; x < tables.size(); x++)
		{
			if (tables[x] == m_createTableDialog.getTableName())
			{
				m_createTableDialog.labelWarning("Already use");
				return;
			}
		}
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
void BTables::MainWindow::on_deleteTableButton_clicked()
{
	if (isAnyTableExists())
	{
		m_db->removeTable(getCurrentTableName());
		updateTablesList();
		if (isAnyTableExists())
		{
			loadFirstExistsTable();
		}
		else
		{
			m_mainForm.currentTable->setRowCount(0);
			m_mainForm.currentTable->setColumnCount(0);
			m_mainForm.currentTable->clear();
		}
	}
}
void BTables::MainWindow::on_removeFieldButton_clicked()
{
	if (isAnyTableExists() && m_mainForm.currentTable->rowCount() > 1)
	{
		const size_t currentRow = m_mainForm.currentTable->currentRow();
		if (currentRow == SIZE_MAX)
		{
			warnMessage("Any row wasn`t select");
			return;
		}
		m_db->removeField(getCurrentTableName(), currentRow);
		loadTable(getCurrentTableName());
		infoMessage("Succeful remove field");
	}
}
void BTables::MainWindow::on_viewButton_clicked()
{
	if (isAnyTableExists())
	{
		if (m_windowState == MainMenu)
		{		
			m_windowState = GuessMenu;
			setOtherButtonsEnabled(false);
			m_mainForm.viewButton->setText("View errors");

			const size_t iColumns = m_mainForm.currentTable->columnCount();
			const size_t iRows = m_mainForm.currentTable->rowCount();
			QVector<TableRow> tableData = m_db->getDataOfTable(getCurrentTableName());
			m_mainForm.currentTable->blockSignals(true);

			// 1. Clear all items except first column
			for (size_t y = 0; y < iRows; y++)
			{
				for (size_t x = 1; x < iColumns; x++)
				{
					QTableWidgetItem* item = new QTableWidgetItem();
					item->setData(Qt::EditRole, "");
					m_mainForm.currentTable->setItem(y, x, item);
				}
			}

			// 2. First column must editable and with mixed data
			QVector<QString> mixedData;
			for (size_t x = 0; x < iRows; x++)
			{
				mixedData.push_back(tableData[x][0]);
			}
			unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
			std::mt19937 gen(ms);
			std::shuffle(mixedData.begin(), mixedData.end(), gen);

			for (size_t y = 0; y < iRows; y++)
			{
				QTableWidgetItem* item = new QTableWidgetItem();
				item->setData(Qt::DisplayRole, mixedData[y]);
				forbidChangeItem(item);
				item->setBackground(QBrush((QColor(31, 31, 31, 130))));
				m_mainForm.currentTable->setItem(y, 0, item);
			}
			m_mainForm.currentTable->blockSignals(false);
			return;


			// 3. Add any place in window button to end try
			// 4. Show window with results
			// 5. Return old position of items
		}
		if (m_windowState == GuessMenu)
		{
			m_windowState = ErrorMenu;
			m_mainForm.viewButton->setText("View");

			//Make results and debug this
			GuessResults results = makeResults(getCurrentTableState());
			infoMessage("Total answers: " + QString::number(results.totalAnswers));
			infoMessage("True answers: " + QString::number(results.trueAnswers));

			//Forbid change items when displayed the errors
			const size_t iColumns = m_mainForm.currentTable->columnCount();
			const size_t iRows = m_mainForm.currentTable->rowCount();
			for (size_t y = 0; y < iRows; y++)
			{
				for (size_t x = 0; x < iColumns; x++)
				{
					forbidChangeItem(m_mainForm.currentTable->item(y, x));
				}
			}

			infoMessage("Count of erros places: " + QString::number(results.errorPlaces.size()));

			//Highlight the errors and true answers
			for (size_t iy = 0; iy < iRows; iy++)
			{
				for (size_t ix = 1; ix < iColumns; ix++)
				{
					auto item = m_mainForm.currentTable->item(iy, ix);
					bool wasError = false;
					for (size_t x = 0; x < results.errorPlaces.size(); x++)
					{
						if (results.errorPlaces[x].m_x == ix && results.errorPlaces[x].m_y == iy)
						{
							infoMessage("Error x: " + QString::number(iy) + " y: " + QString::number(ix));
							item->setBackground(QBrush((QColor(121, 0, 0, 130))));
							wasError = true;
							break;
						}
					}
					if (!wasError)
					{
						item->setBackground(QBrush((QColor(0, 121, 0, 130))));
					}
				}
			}
			
			m_guessResultsDialog.showResults(results);
			return;
		}
		if (m_windowState == ErrorMenu)
		{
			m_windowState = MainMenu;
			m_guessResultsDialog.terminate();
			m_mainForm.viewButton->setText("Try");
			setOtherButtonsEnabled(true);
			loadTable(getCurrentTableName());
			return;
		}
	}
}
