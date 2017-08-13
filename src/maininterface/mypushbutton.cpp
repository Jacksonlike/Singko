#include <mypushbutton.h>
#include <QDebug>

MyPushbutton::MyPushbutton(QWidget *parent)
            : QPushButton(parent)
{
    setStyleSheet("QPushButton{background-color:transparent}\
                  QPushButton:hover{background-color:#a5face;}");
}

MyPushbutton::~MyPushbutton()
{

}

void MyPushbutton::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
    QPushButton::mousePressEvent(event);
}
