#pragma once
#include <Include.h>
#include <MainWindow.h>

namespace BTables
{
	class MainWindow;

	class DeleteTableCommand : public QUndoCommand
	{
		MainWindow* m_mainWindow;
		QString m_serializeData;
		QString m_tableName;
		size_t m_columns;
		size_t m_index;
	public:
		DeleteTableCommand(MainWindow* mainWindow, const QString tableName);
		void undo() override;
		void redo() override;
		~DeleteTableCommand() {}
	};
}

