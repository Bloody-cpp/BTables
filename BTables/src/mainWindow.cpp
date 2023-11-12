#include "mainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	this->setObjectName("MainWindow");
	this->setStyleSheet("#MainWindow { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #03fcca, stop: 1.0 #8936d6); }");

	m_mainForm.setupUi(this);
	m_mainForm.availableTables->addItem("Hello world!");
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton &&
		event->modifiers() == Qt::NoModifier)
	{
		m_dragPosition = event->globalPos();
		setCursor(Qt::ClosedHandCursor);
		return;
	}
	QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (m_dragPosition == kInvalidPoint)
		return QWidget::mouseMoveEvent(event);

	const QPoint delta = event->globalPos() - m_dragPosition;
	move(pos() + delta);
	m_dragPosition = event->globalPos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
	m_dragPosition = kInvalidPoint;
	setCursor(Qt::OpenHandCursor);
	QWidget::mouseReleaseEvent(event);
}

void MainWindow::on_closeButton_clicked()
{
	QCoreApplication::quit();
}