#include "MainWindow.h"

BTables::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

	m_mainForm.setupUi(this);
	m_mainForm.availableTables->addItem("Hello world!");
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

void BTables::MainWindow::on_createTableButton_clicked()
{
	m_createTableDialog.exec();
}