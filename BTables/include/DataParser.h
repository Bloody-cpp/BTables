#pragma once
#include <Include.h>

namespace BTables
{
	QString addToSerialize(const QString data, const QVector<QString> addData);
	QString serialize(const QVector<QVector<QString>> data);
	QVector<QVector<QString>> parseData(const QString data);
}