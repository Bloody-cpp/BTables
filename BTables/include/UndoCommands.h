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

	class DeleteFieldCommand : public QUndoCommand
	{
		MainWindow* m_mainWindow;
		TableY m_coord;
		TableRow m_data;
		QString m_tableName;
	public:
		DeleteFieldCommand(MainWindow* mainWindow, const TableY coord);
		void undo() override;
		void redo() override;
		~DeleteFieldCommand() {}
	};

	class EditCellCommand : public QUndoCommand
	{
		MainWindow* m_mainWindow;
		TableCoord m_coord; 
		QString m_tableName;
		QString m_oldData;
		QString m_newData;
	public:
		EditCellCommand(MainWindow* mainWindow, const TableCoord coord, const QString newData, const QString oldData);
		void undo() override;
		void redo() override;
		~EditCellCommand() {};
	};

	class FieldCreateCommand : public QUndoCommand
	{
		MainWindow* m_mainWindow;
		QString m_tableName;
	public:
		FieldCreateCommand(MainWindow* mainWindow);
		void undo() override;
		void redo() override;
		~FieldCreateCommand() {}
	};
}

