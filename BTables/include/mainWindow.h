#pragma once
#include <Include.h>
#include <ui_mainWindowForm.h>
#include <CreateTableDialog.h>
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

		DataBase* m_db;
	public:
		MainWindow(QWidget* parent = nullptr);
		~MainWindow() {}
	protected:
		void mousePressEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
	private:
		void updateTablesList();
	public slots:
		void on_createTableConfirm();
		void on_closeButton_clicked();
		void on_availableTables_itemClicked(QListWidgetItem* item);
		void on_createTableButton_clicked();
	};
}