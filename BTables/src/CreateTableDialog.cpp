#include "CreateTableDialog.h"

BTables::CreateTableDialog::CreateTableDialog(QWidget* parent) : QDialog(parent)
{
	m_dialog.setupUi(this);
}

QString BTables::CreateTableDialog::getTableName()
{
	return m_dialog.tableName->text();
}

qint16 BTables::CreateTableDialog::getNumberColumns()
{
	return m_dialog.numberOfColumns->value();
}

Ui::CreateTableDialogForm* BTables::CreateTableDialog::getUI()
{
	return &m_dialog;
}

bool BTables::CreateTableDialog::checkEmpty()
{
	if (getTableName().isEmpty())
	{
		m_dialog.tableNameLabel->setText("Fill this");
		return false;
	}
	return true;
}