#pragma once
#include <Include.h>
#include <ui_debugWindow.h>

namespace BTables
{
	class DebugWindow : public QWidget
	{
		Q_OBJECT

		Ui::DebugWindow m_debugWindow;
	public:
		explicit DebugWindow();
		void pushMessage(const QString type, const QString message);
		~DebugWindow();
	};

	extern DebugWindow* debugWindow;
	
	void sqlMessage(QSqlQuery* query, const QString message);
	void warnMessage(const QString message);
	void fatalMessage(const QString message);
	void errorMessage(const QString message);
	void infoMessage(const QString message);
}