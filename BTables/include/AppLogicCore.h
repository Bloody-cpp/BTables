#pragma once
#include <DefaultInclude.h>
#include <MainWindow.h>
#include <DataBase.h>
#include <DebugWindow.h>
#include <CreateTableDialog.h>

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
		void updateTablesList();
	public slots:
		void onSelectTable(QListWidgetItem* clickedItem);
		void onCreateNewTable(const CreateTableDialog::Data data);
		void onExit();
	};
}
