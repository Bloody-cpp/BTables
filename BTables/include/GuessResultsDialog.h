#pragma once
#include <Include.h>
#include <ui_guessResultsDialog.h>

namespace BTables
{
	struct TableCoord
	{
		TableCoord(size_t x, size_t y) : m_x(x), m_y(y) {}
		size_t m_x;
		size_t m_y;
	};

	struct GuessResults
	{
		size_t totalAnswers = 0;
		size_t trueAnswers = 0;
		QVector<TableCoord> errorPlaces;
	};

	class GuessResultsDialog : public QDialog
	{
		Q_OBJECT

		Ui::GuessResultsDialog m_dialog;
	public:
		explicit GuessResultsDialog(QWidget* parent = nullptr);
		void showResults(const GuessResults results);
		void terminate();
		~GuessResultsDialog();
	public slots:
		void on_continueButton_pressed();
	};

}
