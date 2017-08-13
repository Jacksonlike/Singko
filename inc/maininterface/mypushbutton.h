#ifndef MYPUSHBOOTN
#define MYPUSHBOOTN
#include <QPushButton>

class MyPushbutton:public QPushButton
{
    Q_OBJECT
public:
    MyPushbutton(QWidget *parent = 0);
    ~MyPushbutton();

    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYPUSHBOOTN

