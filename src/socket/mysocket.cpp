#include "mysocket.h"
#include "ownMessage.h"
#include <QHostAddress>
#include "userMessage.h"

Mysocket::Mysocket(QObject *parent) : QObject(parent)
{
    flag = 0;//为0时表示刚建立udpsocket,需要发送广播
    udpsocket = new QUdpSocket(this);
    ownMessage *mymessage = new ownMessage;
    udpsocket->bind(QHostAddress(mymessage->getLocalIP()),50001);
    qDebug()<<mymessage->getLocalIP();
    connect(udpsocket, SIGNAL(readyRead()),
            this,SLOT(rec_message()));
}

void Mysocket::sendMessage(QHostAddress ipaddr,QString str)
{

    if(flag == 0)//刚上线，需要广播自己的信息
    {
        qDebug()<<"111,shangxian";
        ownMessage *mymessage = new ownMessage;
        send_mes.setSendText(0,mymessage);
       int n = udpsocket->writeDatagram(send_mes.getSendText(),
                   send_mes.getSendText().size(),
                   QHostAddress::Broadcast,50001);
        qDebug()<<n;
        delete mymessage;       
        flag = 2;//状态转换为已上线
    }

    else if(flag == 2)//已上线，可正常聊天
    {
        qDebug()<<"222,chating";
        send_mes.setSendText(2,str);
        udpsocket->writeDatagram(send_mes.getSendText(),
                                 send_mes.getSendText().size(),
                                 ipaddr, 50001);
    }
    send_mes.cleanSend();
}

void Mysocket::rec_message()
{
    qDebug()<<"mmmmmmmmmmmmm";
    char buf[1024];
    QHostAddress sender_ip;
    quint16 sender_port;

    int n = udpsocket->readDatagram(buf, 1024,&sender_ip,&sender_port);
    qDebug()<<n;
    if(sender_port != 50001)
        return ;

    rec_mes.setRevText(buf);


    //1.收到的为好友广播，需要回复自己信息，并加入好友列表
    if(*buf == '0' && sender_ip != QHostAddress::LocalHost)
    {
        qDebug()<<"333,somecome";
        ownMessage *mymessage = new ownMessage;
        send_mes.setSendText(1,mymessage);
        udpsocket->writeDatagram(send_mes.getSendText(),
                                 send_mes.getSendText().size(),
                                 sender_ip, 50001);
       send_mes.cleanSend();
       delete mymessage;

       emit sigAddFriend(rec_mes.getRevMessage());
    }

    else if(*buf == '1')//收到的为好友回复的信息，加入好友列表
    {
        qDebug()<<"444,somechat";
        emit sigAddFriend(rec_mes.getRevMessage());
    }
    else if(*buf == '2')//收到的为好友聊天信息，加入窗口聊天框
    {
        qDebug()<<"555,somechat";
        emit sigRevText(rec_mes.getRevText(),sender_ip);
    }
    rec_mes.cleanRev();
}

