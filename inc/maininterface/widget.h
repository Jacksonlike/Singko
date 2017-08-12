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
#include "mysocket.h"

#include <QtDebug>
//#define  DEBUG_WIDTH

//==============================================================
/*                       main interface
** 初始化界面需要包含主要功能控件的加载，以及获取自己的设置信息和在线用户列
** 表。此外有信号和槽接口与子界面进行通信。
**
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
    void setBackground(int num);
    void setHeadprotrait(int num);
    void setUsrname(QString name);
    void setSignature(QString signature);


private slots:
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_About_Button_clicked();
    void on_mini_pushbutton_clicked();

    void on_close_pushbutton_clicked();

private:
    Ui::Widget *ui;
    ownMessage* master;
    Toolbox *usrlist;
    LineEdit *signature;
    QSystemTrayIcon *mSysTrayIcon;
    MyPushbutton *Setting_Button;
    MyPushbutton *Sharing_Button;
    MyPushbutton *About_Button;
    QPoint dPos;
 //   Mysocket *myudp_socket;

//    Toolbox *grouplist;
//    Toolbox *recentist;
};

#endif // WIDGET_H

