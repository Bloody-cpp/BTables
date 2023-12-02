#include "DebugWindow.h"

BTables::DebugWindow::DebugWindow() : QWidget()
{
	m_debugWindow.setupUi(this);
}

void BTables::DebugWindow::sqlMessage(QSqlQuery* query, const QString message)
{
	QString debugString = debugFormat.arg(QDateTime().currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
	if (query->exec())
	{
		debugString = debugString.arg("SQL");
	}
	else
	{
		debugString = debugString.arg("ERROR SQL");
	}
	debugString = debugString.arg(message);
	m_debugWindow.console->append(debugString);
}

void BTables::DebugWindow::warnMessage(const QString message)
{
	QString debugString = debugFormat;
	debugString = debugString.arg(QDateTime().currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
	debugString = debugString.arg("WARN");
	debugString = debugString.arg(message);
	m_debugWindow.console->append(debugString);
}

void BTables::DebugWindow::fatalMessage(const QString message)
{
	QString debugString = debugFormat;
	debugString = debugString.arg(QDateTime().currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
	debugString = debugString.arg("FATAL");
	debugString = debugString.arg(message);
	m_debugWindow.console->append(debugString);
}

void BTables::DebugWindow::errorMessage(const QString message)
{
	QString debugString = debugFormat;
	debugString = debugString.arg(QDateTime().currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
	debugString = debugString.arg("ERROR");
	debugString = debugString.arg(message);
	m_debugWindow.console->append(debugString);
}

void BTables::DebugWindow::infoMessage(const QString message)
{
	QString debugString = debugFormat;
	debugString = debugString.arg(QDateTime().currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
	debugString = debugString.arg("INFO");
	debugString = debugString.arg(message);
	m_debugWindow.console->append(debugString);
}

BTables::DebugWindow& BTables::DebugWindow::operator<<(const QString message)
{
	return *this;
}

BTables::DebugWindow::~DebugWindow()
{
}
