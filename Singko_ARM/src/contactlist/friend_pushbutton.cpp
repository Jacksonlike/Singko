#include "friend_pushbutton.h"
#include <toolbox.h>

FriendPushbutton::FriendPushbutton(userMessage *u,QWidget *parent)
    :QPushButton(parent), user(u), push_flag(0)
{
    twinkle.setInterval(500);
    connect(&twinkle, SIGNAL(timeout()),this, SLOT(buttonTwinkle()));
    this->setdefaultStytle();

}


FriendPushbutton::~FriendPushbutton()
{
    delete user;
}


void FriendPushbutton::setdefaultStytle()
{
    this->setStyleSheet(""
    "QPushButton{border-radius: 5px;  border: 2px groove gray;\
                border-style: outset;text-align:left;font-size: 9pt;}"
    "QPushButton:hover{background-color : #FAFAF0;text-align:left;font-size: 9pt;}"
    "QPushButton:pressed{background-color : #FFFFFF;border-style: inset;font-size: 9pt;}");
}

void FriendPushbutton::settwinkleStytle()
{
    this->setStyleSheet(""
    "QPushButton{background-color : #FCFFC0;border-radius: 5px;  border: 2px groove gray;\
                border-style: outset;text-align:left;font-size: 9pt;}"
    "QPushButton:hover{background-color : #FAFAF0;text-align:left;font-size: 9pt;}"
    "QPushButton:pressed{background-color : #FFFFFF;border-style: inset;font-size: 9pt;}");
}


void FriendPushbutton::mousePressEvent(QMouseEvent *event)
{
    setFlag(1);//表示窗口被点开
    ChatWindow *myfriend = new ChatWindow(0, user);
    connect(myfriend,SIGNAL(chatWindowclosed()),this,SLOT(closeWindow()));
    connect(this,SIGNAL(sigButtonMessage(QString)),myfriend,SLOT(slot_button_message(QString)));
    //读取对应好友消息记录，并显示
    myfriend->show();
    if(twinkle.isActive())
    {
        emit sigButtonMessage(friendmessage);
        twinkle.stop();
        setdefaultStytle();
        this->repaint();
    }

    QPushButton::mousePressEvent(event);
}
void FriendPushbutton::buttonTwinkle()
{
    static bool flag = true;
    qDebug()<<"flag = "<<flag;
    if(flag)
    {

        this->settwinkleStytle();
        this->repaint();
        flag = false;
    }
    else
    {
        this->setdefaultStytle();
        this->repaint();
        flag = true;
    }
}

void FriendPushbutton::closeWindow()
{
    setFlag(0);
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
            qDebug()<<"friend message!";
            friendmessage = str;
            twinkle.start();

        }
        else if(getFlag() ==1)
        {
            emit sigButtonMessage(str);//给窗口发信号显示消息
        }
}
    //将消息记录写入对应文件

}


