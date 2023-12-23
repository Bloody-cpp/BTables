#include "Debug.h"

namespace BTables
{
	DebugWindow* debugWindow = nullptr;
}

BTables::DebugWindow::DebugWindow() : QWidget()
{
	m_debugWindow.setupUi(this);
	this->show();
}

void BTables::DebugWindow::pushMessage(const QString type, const QString message)
{
	if (debugWindow == nullptr)
	{
		QCoreApplication::quit();
	}

	QString debugString = "[%1] [%2] %3";
	debugString = debugString.arg(QDateTime().currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
	debugString = debugString.arg(type);
	debugString = debugString.arg(message);
	m_debugWindow.console->append(debugString);
}

void BTables::setupDebugWindow(DebugWindow* ptrWindow)
{
	debugWindow = ptrWindow;
}

void BTables::sqlMessage(QSqlQuery* query, const QString message)
{
	if (query->exec())
	{
		debugWindow->pushMessage("SQL", message);
	}
	else
	{
		debugWindow->pushMessage("ERROR SQL", message);
	}
}

void BTables::warnMessage(const QString message)
{
	debugWindow->pushMessage("WARN", message);
}

void BTables::fatalMessage(const QString message)
{
	debugWindow->pushMessage("FATAL", message);
}

void BTables::errorMessage(const QString message)
{
	debugWindow->pushMessage("ERROR", message);
}

void BTables::infoMessage(const QString message)
{
	debugWindow->pushMessage("INFO", message);
}

BTables::DebugWindow::~DebugWindow()
{
}
