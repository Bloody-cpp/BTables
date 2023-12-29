#pragma once
#include <Include.h>
#include <ui_mainWindowForm.h>
#include <CreateTableDialog.h>
#include <SetColumnsDialog.h>
#include <DataBase.h>
#include <Debug.h>

namespace BTables
{
	constexpr QPoint kInvalidPoint(-1, -1);

	class MainWindow : public QMainWindow
	{
		Q_OBJECT
		QPoint m_dragPosition;

		Ui::MainWindowForm m_mainForm;
		CreateTableDialog m_createTableDialog;
		SetColumnsDialog m_setColumnsDialog;
		DebugWindow* m_debugWindow;
		DataBase* m_db;
	public:
		MainWindow(QWidget* parent = nullptr);
		~MainWindow() {}
	protected:
		void mousePressEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
	private:
		QString getCurrentTableName();
		void loadTable(const QString tableName);
		void updateTablesList();
		bool isAnyTableExists();
	public slots:
		//Dialog end slots
		void on_createTableConfirm();
		void on_setColumnsConfirm();

		//Dialog start slots
		void on_createTableButton_clicked();
		void on_setColumnsButton_clicked();

		//Main ui slots
		void on_currentTable_itemChanged(QTableWidgetItem* item);
		void on_closeButton_clicked();
		void on_availableTables_itemClicked(QListWidgetItem* item);
		void on_addFieldButton_clicked();
	};
}