#ifndef LINEEDIT
#define LINEEDIT


#include <QWidget>
#include <QLineEdit>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);
    inline void Editting();
    inline void OutEdit();

signals:

public slots:
};

inline void LineEdit::Editting()
{
    setStyleSheet("background-color : #ffffffff;\
                    border-width:0;\
                    border-style:outset");
}

inline void LineEdit::OutEdit()
{
    setStyleSheet("background:transparent;\
                    border-width:0;\
                    border-style:outset");
}


#endif // LINEEDIT

