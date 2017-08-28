#ifndef FRIEND_PUSHBUTTON_H
#define FRIEND_PUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include "userMessage.h"
#include <QHostAddress>
#include "chatwindow.h"
#include <Qtimer>

//==============================================================
/*                        FriendPushbutton
** 上线好友显示的按钮
** buttonTwinkle：收到消息闪烁（当收到好友消息，若对应聊天窗口没有打开，
** 则开启定时器周期性切换样式表，实现闪烁功能）
*/
//==============================================================


class FriendPushbutton:public QPushButton
{
    Q_OBJECT
public:
    FriendPushbutton(userMessage* u, QWidget *parent = 0);

    ~FriendPushbutton();

    inline int  getFlag();
    inline void setFlag(int n);
    inline userMessage * getUser();
    void setdefaultStytle();
    void settwinkleStytle();

public slots:
    void revFriendMessage(QString str, QHostAddress ipaddr);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void buttonTwinkle();
    void closeWindow();

signals:
    void sigButtonMessage(QString str);

private:
    userMessage *user;
    QTimer twinkle;
    QString friendmessage;
    int pushFlag;       //用来标记聊天窗是否已打开
    bool buttonFlag;    //用来标记按钮当前显示的状态
};


inline void FriendPushbutton::setFlag(int n)
{
    pushFlag = n;
}

inline userMessage *FriendPushbutton::getUser()
{
    return user;
}

inline int FriendPushbutton::getFlag()
{
    return pushFlag;
}

#endif // FRIEND_PUSHBUTTON_H
