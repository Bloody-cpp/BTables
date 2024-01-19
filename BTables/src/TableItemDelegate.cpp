#include "TableItemDelegate.h"

QWidget* BTables::TableItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return new QLineEdit(parent);
}

void BTables::TableItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(index.model()->data(index, Qt::EditRole).toString());
}

void BTables::TableItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    m_oldValue = index.model()->data(index, Qt::EditRole).toString();
    model->setData(index, lineEdit->text(), Qt::EditRole);
}

void BTables::TableItemDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}

QString BTables::TableItemDelegate::getOldValue()
{
    return m_oldValue;
}
