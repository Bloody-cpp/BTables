#include "GuessResultsDialog.h"

BTables::GuessResultsDialog::GuessResultsDialog(QWidget* parent) : QDialog(parent)
{
	m_dialog.setupUi(this);
}

void BTables::GuessResultsDialog::showResults(const GuessResults results)
{
	if (this->isVisible())
	{
		done(0);
	}
	m_dialog.totalAnswersLabel->setText("Total answers: " + QString::number(results.totalAnswers));
	m_dialog.typeTotalErros->setText(QString::number(results.totalAnswers - results.trueAnswers));
	m_dialog.typeTrueAnswers->setText(QString::number(results.trueAnswers));
	show();
}

void BTables::GuessResultsDialog::terminate()
{
	done(0);
}

void BTables::GuessResultsDialog::on_continueButton_pressed()
{
	done(0);
}

BTables::GuessResultsDialog::~GuessResultsDialog()
{

}
