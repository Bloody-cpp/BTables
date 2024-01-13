#pragma once
#include <Include.h>
#include <ui_mainWindowForm.h>
#include <CreateTableDialog.h>
#include <SetColumnsDialog.h>
#include <GuessResultsDialog.h>
#include <DataBase.h>
#include <Debug.h>
#include <TableItem.h>

// In future:
// 1. Add table with delete tables and posibility to recovery
// 2. Add table with statistics of last tryes
// All things upper must releaseted with one class which can do that
// 3. Add hotkeys to create table, delete table (needs have difference between delete table and row)
//		that can be realease with boolean value of last clicked current item in both tables
// 4. Add feature to import/export tables to excel
// 5. Using json to save data of table
// 6. Make full frameless window with resize feature

// 7. make key combination ctrl + z to recovery removed fields and tables

namespace BTables
{
	constexpr QPoint kInvalidPoint(-1, -1);

	enum GuessState
	{
		MainMenu,
		GuessMenu,
		ErrorMenu
	};

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

		Ui::MainWindowForm m_mainForm;
		CreateTableDialog m_createTableDialog;
		SetColumnsDialog m_setColumnsDialog;
		GuessResultsDialog m_guessResultsDialog;
		DebugWindow* m_debugWindow;
		DataBase* m_db;
		QPoint m_dragPosition;
		GuessState m_windowState = MainMenu;
	public:
		MainWindow(QWidget* parent = nullptr);
		~MainWindow() {}
	protected:
		void mousePressEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
		void keyPressEvent(QKeyEvent* event) override;
	private:
		bool isAnyTableExists();
		QString getCurrentTableName();
		void loadTable(const QString tableName);
		void updateTablesList();
		void loadFirstExistsTable();
		void setOtherButtonsEnabled(const bool state);
		QVector<TableRow> getCurrentTableState();
		size_t searchRowByFirstValue(const QVector<TableRow> rows, const QString fValue);
		GuessResults makeResults(const QVector<TableRow> currentTableState);
		void forbidChangeItem(QTableWidgetItem* item);
		void accessChangeItem(QTableWidgetItem* item);
		void setSelectionIn(const size_t row, const size_t column);
		bool eventFilter(QObject* object, QEvent* event);
		QTableWidgetItem* getCurrentItem();
	public slots:
		//Dialog end slots
		void on_createTableConfirm();
		void on_setColumnsConfirm();

		//Dialog start slots
		void on_createTableButton_clicked();
		void on_setColumnsButton_clicked();

		//Main ui slots 
		void on_currentTable_itemChanged(QTableWidgetItem* item); 
		void on_currentTable_itemClicked(QTableWidgetItem* item);
		void on_availableTables_itemClicked(QListWidgetItem* item);
		void on_addFieldButton_clicked();
		void on_closeButton_clicked();
		void on_deleteTableButton_clicked();
		void on_removeFieldButton_clicked();
		void on_viewButton_clicked();
	};
}