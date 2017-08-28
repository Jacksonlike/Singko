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
    void display();
    ~Widget();

public slots:
    void setBackground(int num);
    void setHeadprotrait(int num);
    void setUsrname(QString name);


private slots:
    void on_close_pushbutton_clicked();


private:
    Ui::Widget *ui;
    ownMessage* master;
    Toolbox *usrlist;
    QSystemTrayIcon *mSysTrayIcon;
    MyPushbutton *Setting_Button;
    MyPushbutton *Sharing_Button;

};

#endif // WIDGET_H

