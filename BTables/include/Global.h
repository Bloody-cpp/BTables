#pragma once
#include <DefaultInclude.h>
#include <DataBase.h>
#include <MainWindow.h>
#include <DebugWindow.h>

namespace BTables
{
	struct AppData
	{
		MainWindow* mainWindow;
		DataBase* database;
		Debugger debug;
	};
}