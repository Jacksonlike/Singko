#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <ownMessage.h>
#include <toolbox.h>
#include <lineedit.h>
#include <QMessageBox>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <mypushbutton.h>
#include <QTimer>
#include <QPropertyAnimation>
#include "mysocket.h"

#include <QtDebug>
//#define  DEBUG_WIDTH

//==============================================================
/*                       main interface
** 完成界面的初始化。
*/
//==============================================================
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void display();
    ~Widget();

public slots:
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);
    void setBackground(int num);
    void setHeadprotrait(int num);
    void setUsrname(QString name);
    void setSignature(QString signature);


private slots:
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_About_Button_clicked();
    void on_mini_pushbutton_clicked();
    void on_close_pushbutton_clicked();
    void updateHide();
    void updateShow();
    void updateInter();
    bool HideOrNot();
    bool ShowOrNot();

private:
    Ui::Widget *ui;
    ownMessage* master;
    Toolbox *usrlist;
    LineEdit *signature;
    QSystemTrayIcon *mSysTrayIcon;
    MyPushbutton *Setting_Button;
    MyPushbutton *Sharing_Button;
    MyPushbutton *About_Button;
    QTimer *timer_Hide;
    QTimer *timer_Show;
    QTimer *timer_Inter;
    QPropertyAnimation *edgeMoveAnimation;
    QPoint dPos;
    int EdgeMoveTime;
    int EdgeHideTime;
    bool mov;

 //   Mysocket *myudp_socket;

//    Toolbox *grouplist;
//    Toolbox *recentist;
};

#endif // WIDGET_H

