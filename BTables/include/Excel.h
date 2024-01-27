#pragma once
#include <Include.h>
#include <Debug.h>
#include <QXlsx/header/xlsxdocument.h>
//#include <lib/xlsx/xlsxchartsheet.h>
//#include <lib/xlsx/xlsxcellrange.h>
//#include <lib/xlsx/xlsxchart.h>
//#include <lib/xlsx/xlsxrichstring.h>
//#include <lib/xlsx/xlsxworkbook.h>

using namespace QXlsx;

namespace BTables
{

	class ExcelIO : public QObject
	{
		Q_OBJECT

	public:
		ExcelIO(QObject* parent = nullptr);
		TableData importFile(const QString path);
		void exportFile(const QString path, const TableData data);
		~ExcelIO();
	};
}