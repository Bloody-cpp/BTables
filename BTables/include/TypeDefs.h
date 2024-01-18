#pragma once
#include <Include.h>

namespace BTables
{
	using TableRow = QVector<QString>;
	using TableColumn = QVector<QString>;
	using TableData = QVector<QVector<QString>>;
	
	using TableY = size_t;
	using TableX = size_t;

	struct TableCoord
	{
		TableCoord(TableX x, TableY y) : m_x(x), m_y(y) {}
		TableX m_x;
		TableY m_y;
	};
}