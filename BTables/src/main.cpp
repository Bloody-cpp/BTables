#include <DefaultInclude.h>
#include <AppLogicCore.h>

using namespace Qt;

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	BTables::AppLogicCore logicCore;

	return app.exec();
}