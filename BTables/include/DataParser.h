#pragma once
#include <Include.h>

namespace BTables
{
	QString addToSerialize(const QString data, const TableRow addData);
	QString serialize(const TableData data);
	TableData parseData(const QString data);
}