#pragma once
#include <DefaultInclude.h>
#include <MainWindow.h>
#include <DataBase.h>
#include <DebugWindow.h>

namespace BTables
{
	class AppLogicCore : public QObject
	{
		Q_OBJECT

		MainWindow m_mainWindow;
		DataBase* m_database;
		Debugger m_debug;
	public:
		explicit AppLogicCore(QObject* parent = nullptr);
		~AppLogicCore();
	private:
		void initializeListTables();
	public slots:
		void onSelectTable(QListWidgetItem* clickedItem);
	};
}
