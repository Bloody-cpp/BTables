#pragma once
#include <DefaultInclude.h>
#include <ui_debugWindow.h>

namespace BTables
{
	class DebugWindow : public QWidget
	{
		Q_OBJECT

		Ui::DebugWindow m_debugWindow;
	public:
		QString debugFormat = "[%1] [%2] %3";

		explicit DebugWindow();
		void sqlMessage(QSqlQuery* query, const QString message);
		void warnMessage(const QString message);
		void fatalMessage(const QString message);
		void errorMessage(const QString message);
		void infoMessage(const QString message);
		/**
		 * @brief operator which can auto using correct type of a message
		 * @param message message with modificator: sql, warn, fatal, error, info and ":" in end
		*/
		DebugWindow& operator<<(const QString message);
		~DebugWindow();
	};

	using Debugger = DebugWindow*;
}