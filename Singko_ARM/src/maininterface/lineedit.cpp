#include <lineedit.h>
#include <QtDebug>
#include <QKeyEvent>

LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent)
{
    OutEdit();
}

void LineEdit::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    Editting();
    QLineEdit::mousePressEvent(event);
}

void LineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        OutEdit();
        clearFocus();
    }
    QLineEdit::keyPressEvent(event);
}

void LineEdit::focusOutEvent(QFocusEvent *event)
{
    OutEdit();
    QLineEdit::focusOutEvent(event);
}

void LineEdit::focusInEvent(QFocusEvent *event)
{
    Editting();
    QLineEdit::focusInEvent(event);
}

