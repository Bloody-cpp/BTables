#pragma once
#include <defaultInclude.h>
#include <ui_mainWindowForm.h>

constexpr QPoint kInvalidPoint(-1, -1);

class MainWindow : public QMainWindow
{
	Q_OBJECT

	Ui::MainWindowForm m_mainForm;
    QPoint m_dragPosition;
public: 
	MainWindow(QWidget* parent = nullptr);
	~MainWindow() {}
protected:
    void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
public slots:
	void on_closeButton_clicked();
};

