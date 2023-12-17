#include "Global.h"

namespace BTables
{
	namespace Global
	{
		MainWindow* mainWindow = new MainWindow();
		DataBase* database = new DataBase(mainWindow);
		Debugger debug = new DebugWindow();
	}
}