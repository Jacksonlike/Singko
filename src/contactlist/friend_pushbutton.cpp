#include "friend_pushbutton.h"





Friend_Pushbutton::Friend_Pushbutton(userMessage *u, QWidget *parent)
    :QPushButton(parent)
{
    push_flag = 0; //表示窗口未打开
    user = new userMessage;
    user = u;
    qDebug()<<user->getIP();
}

int Friend_Pushbutton::get_flag()
{
    return push_flag;
}

void Friend_Pushbutton::set_flag(int n)
{
    push_flag = n;
}

void Friend_Pushbutton::on_pushButton_clicked()
{

    set_flag(1);//表示窗口被点开
    ChatWindow *myfriend = new ChatWindow(0,user);
    connect(this,SIGNAL(sig_button_message(QString)),myfriend,SLOT(slot_button_message(QString)));
    myfriend->show();
}

void Friend_Pushbutton::rev_friend_message(QString str, QHostAddress ipaddr)
{
    if(ipaddr != QHostAddress(user->getIP()))
        return ;

    else
    {
        if(get_flag() == 0)
        {
            //改变按钮颜色
        }
        else if(get_flag() ==1)
        {
            emit sig_button_message(str);//给窗口发信号显示消息
        }
    }

}


