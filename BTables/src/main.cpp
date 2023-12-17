#include <MainWindow.h>

using namespace Qt;
using namespace BTables;

int main(int argc, char* argv[])
{
	Beep(1000, 1000);
	Sleep(1000);
	QApplication app(argc, argv);
	MainWindow window;
	window.show();
	return app.exec();
}