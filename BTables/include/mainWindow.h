#pragma once
#include <DefaultInclude.h>
#include <ui_mainWindowForm.h>
#include <CreateTableDialog.h>

namespace BTables
{
	constexpr QPoint kInvalidPoint(-1, -1);

	class MainWindow : public QMainWindow
	{
		Q_OBJECT
		QPoint m_dragPosition;
	public:
		Ui::MainWindowForm m_mainForm;
		CreateTableDialog m_createTableDialog;

		MainWindow(QWidget* parent = nullptr);
		~MainWindow() {}
	protected:
		void mousePressEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
	public slots:
		void on_createTableButton_clicked();
	};
}