#include "SetColumnsDialog.h"

SetColumnsDialog::SetColumnsDialog(QWidget* parent) : QDialog(parent)
{
	m_dialog.setupUi(this);
}

short SetColumnsDialog::getNumberColumns()
{
	return m_dialog.numberOfColumns->value();
}

Ui::SetColumnsDialog* SetColumnsDialog::getUI()
{
	return &m_dialog;
}