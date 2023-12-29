#include "DataParser.h"

QString BTables::addToSerialize(const QString data, const QVector<QString> addData)
{
	if (data.isEmpty())
	{
		return addData.join('.');
	}
	else
	{
		return data + ';' + addData.join('.');
	}
}

QString BTables::serialize(const QVector<QVector<QString>> data)
{
	QVector<QString> buffer;
	for (size_t x = 0; x < data.size(); x++)
	{
		buffer.push_back(data[x].join('.'));
	}
	return buffer.join(';');
}

QVector<QVector<QString>> BTables::parseData(const QString data)
{
	QVector<QVector<QString>> buffer;
	QVector<QString> splitRows = data.split(';');
	for (size_t x = 0; x < splitRows.size(); x++)
	{
		buffer.push_back(splitRows[x].split('.'));
	}
	return buffer;
}
