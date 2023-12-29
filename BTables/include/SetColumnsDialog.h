#pragma once
#include <include.h>
#include <ui_setColumnsDialog.h>

class SetColumnsDialog : public QDialog
{
	Q_OBJECT

	Ui::SetColumnsDialog m_dialog;
public:
	explicit SetColumnsDialog(QWidget* parent = nullptr);
	short getNumberColumns();
	Ui::SetColumnsDialog* getUI();
	~SetColumnsDialog() {};
};

