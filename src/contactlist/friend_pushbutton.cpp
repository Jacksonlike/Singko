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

void FriendPushbutton::on_pushButton_clicked()
{
    setFlag(1);//表示窗口被点开
    ChatWindow *myfriend = new ChatWindow(0, user);
    connect(this,SIGNAL(sigButtonMessage(QString)),myfriend,SLOT(slot_button_message(QString)));
    myfriend->show();
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
        }
        else if(getFlag() ==1)
        {
            emit sigButtonMessage(str);//给窗口发信号显示消息
        }
    }

}


