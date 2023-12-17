#pragma once
#include <DataBase.h>
#include <ui_createTableButtonDialog.h>

namespace BTables
{
	class CreateTableDialog : public QDialog
	{
		Q_OBJECT

		Ui::CreateTableDialogForm m_dialog;
	public:
		explicit CreateTableDialog(QWidget* parent = nullptr);
		QString getTableName();
		qint16 getNumberColumns();
		Ui::CreateTableDialogForm* getUI();
		bool checkEmpty();
		~CreateTableDialog() {};
	};
}