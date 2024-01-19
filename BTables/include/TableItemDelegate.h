#pragma once
#include <Include.h>

namespace BTables
{
	class TableItemDelegate : public QItemDelegate
	{
        Q_OBJECT

        mutable QString m_oldValue;
	public:
        TableItemDelegate(QObject* parent) : QItemDelegate(parent) {}
        QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        void setEditorData(QWidget* editor, const QModelIndex& index) const;
        void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
        void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        QString getOldValue();
		~TableItemDelegate() {};
    };
}

