#include "CreateTableDialog.h"

BTables::CreateTableDialog::CreateTableDialog(QWidget* parent) : QDialog(parent)
{
	m_dialog.setupUi(this);
}

void BTables::CreateTableDialog::on_confirmButton_clicked()
{
	if (m_dialog.tableName->text().isEmpty())
	{
		m_dialog.tableNameLabel->setText("Fill this");
		return;
	}
	this->done(0);
	emit newTable({ m_dialog.tableName->text(), (short)m_dialog.numberOfColumns->value() });
}
