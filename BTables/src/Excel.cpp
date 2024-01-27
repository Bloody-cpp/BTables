#include "Excel.h"

BTables::ExcelIO::ExcelIO(QObject* parent) : QObject(parent)
{
}

BTables::TableData BTables::ExcelIO::importFile(const QString path)
{
	TableData tableData;
	Document* excelFile = new Document(path, this);
	size_t rows = excelFile->dimension().rowCount();
	size_t columns = excelFile->dimension().columnCount();
	for (size_t y = 1; y <= rows; y++)
	{
		TableRow row;
		for (size_t x = 1; x <= columns; x++)
		{
			row.push_back(excelFile->read(y, x).toString());
		}
		tableData.push_back(row);
	}
	delete excelFile;
	return tableData;
}

void BTables::ExcelIO::exportFile(const QString path, const TableData data)
{
	Document* excelFile = new Document(this);
	for (size_t y = 1; y <= data.size(); y++)
	{
		for (size_t x = 1; x <= data[y].size(); x++)
		{
			excelFile->write(y, x, data[y - 1][x - 1]);
		}
	}
	excelFile->saveAs(path);
	delete excelFile;
}

BTables::ExcelIO::~ExcelIO()
{
}
