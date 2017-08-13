#include "friend_pushbutton.h"
#include <toolbox.h>

FriendPushbutton::FriendPushbutton(userMessage *u,QWidget *parent)
    :QPushButton(parent), user(u), push_flag(0)
{
}


FriendPushbutton::~FriendPushbutton()
{
    delete user;
}

void FriendPushbutton::mouseDoubleClickEvent(QMouseEvent *event)
{
    setFlag(1);//表示窗口被点开
    ChatWindow *myfriend = new ChatWindow(0, user);
    connect(this,SIGNAL(sigButtonMessage(QString)),myfriend,SLOT(slot_button_message(QString)));
    //读取对应好友消息记录，并显示
    myfriend->show();
    QPushButton::mouseDoubleClickEvent(event);
}

void FriendPushbutton::revFriendMessage(QString str, QHostAddress ipaddr)
{
    if(ipaddr != QHostAddress(user->getIP()))
        return ;
    else
    {
        if(getFlag() == 0)
        {
            //改变按钮颜色
            this->setStyleSheet("selection-background-color:lightgreen");
            this->repaint();

        }
        else if(getFlag() ==1)
        {
            emit sigButtonMessage(str);//给窗口发信号显示消息
        }
    }
    //将消息记录写入对应文件

}


