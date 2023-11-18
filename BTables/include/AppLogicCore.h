#pragma once
#include <DefaultInclude.h>
#include <MainWindow.h>
#include <DataBase.h>

class AppLogicCore : public QObject
{
	Q_OBJECT

	BTables::MainWindow* m_mainWindow;
	BTables::DataBase* m_database;
public:
	explicit AppLogicCore(QObject* parent);

	~AppLogicCore();
};

