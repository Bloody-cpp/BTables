#pragma once
#include <DefaultInclude.h>
#include <ui_createTableButtonDialog.h>

namespace BTables
{
	class CreateTableDialog : public QDialog
	{
		Q_OBJECT

	public:
		struct Data
		{
			QString m_tableName;
			short m_numberColumns = 0;
		};

		Ui::CreateTableDialogForm m_dialog;
		Data m_data;
		explicit CreateTableDialog(QWidget* parent = nullptr);
		~CreateTableDialog() {};
	signals:
		void newTable(const Data data);
	public slots:
		void on_confirmButton_clicked();
	};
}