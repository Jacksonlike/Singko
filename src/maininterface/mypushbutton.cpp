#include <mypushbutton.h>

MyPushbutton::MyPushbutton(QWidget *parent)
            : QPushButton(parent)
{

}

void MyPushbutton::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);
}

void MyPushbutton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);
}
