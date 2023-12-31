#include <MainWindow.h>

using namespace Qt;
using namespace BTables;

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow window;
	window.show();
	return app.exec();
}