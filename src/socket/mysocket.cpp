#include "mysocket.h"
#include "ownMessage.h"
#include <QHostAddress>
#include "userMessage.h"

Mysocket::Mysocket(QObject *parent) : QObject(parent)
{
    flag = 0;//为0时表示刚建立udpsocket,需要发送广播
    udpsocket = new QUdpSocket(this);
    udpsocket->bind(QHostAddress(ownMessage::getLocalIP()),50001);

    qDebug()<<"Local IP : "<<ownMessage::getLocalIP();

    connect(udpsocket, SIGNAL(readyRead()),
            this, SLOT(recMessage()));
}

void Mysocket::setFlag(int n)
{
    flag =n;
}

Mysocket::~Mysocket()
{
    delete udpsocket;
}

void Mysocket::sendMessage(QHostAddress ipaddr,QString str)
{

    if(flag == 0)//刚上线，需要广播自己的信息
    {
        ownMessage *mymessage = new ownMessage;
        send_mes.setSendText(0, mymessage);
        qint64 n = udpsocket->writeDatagram(send_mes.getSendText(),
                   send_mes.getSendText().size(),
                   QHostAddress::Broadcast, 50001);

        qDebug() << "Online boardcast, write data : " << n;
        delete mymessage;       
        flag = 2;//状态转换为已上线
    }

    else if(flag == 2)//已上线，可正常聊天
    {
        qDebug()<<"Chating";
        send_mes.setSendText(2,str);
        udpsocket->writeDatagram(send_mes.getSendText(),
                                 send_mes.getSendText().size(),
                                 ipaddr, 50001);
    }

    if(flag == -1)//下线广播
    {
        ownMessage *mymessage = new ownMessage;
        send_mes.setSendText(-1, mymessage);
        qint64 n = udpsocket->writeDatagram(send_mes.getSendText(),
                   send_mes.getSendText().size(),
                   QHostAddress::Broadcast, 50001);

        qDebug() << "Close boardcast, write data : " << n;
        delete mymessage;

    }


    send_mes.cleanSend();
}

void Mysocket::recMessage()
{
    while (udpsocket->hasPendingDatagrams())
    {
        int size = udpsocket->pendingDatagramSize();
        char buf[size+1];
        memset(buf,0,size+1);
        QHostAddress sender_ip;
        quint16 sender_port;

        qint64 n = udpsocket->readDatagram(buf, size, &sender_ip, &sender_port);
        qDebug() << "recMessage, read data : " << n;
        if(sender_port != 50001)
            return ;

        rec_mes.setRevText(buf);

        qDebug()<<"*buf = "<<*buf;
        //1.收到的为好友广播，需要回复自己信息，并加入好友列表
        if(*buf == '0' && (sender_ip.toString() != ownMessage::getLocalIP()))
        {
            qDebug()<<"add somecome(*buf == '0')";
            ownMessage *mymessage = new ownMessage;
            send_mes.setSendText(1,mymessage);
            udpsocket->writeDatagram(send_mes.getSendText(),
                       send_mes.getSendText().size(),sender_ip, 50001);
            send_mes.cleanSend();
            delete mymessage;
            emit sigAddFriend(rec_mes.getRevMessage());
        }

        else if(*buf == '1')//收到的为好友回复的信息，加入好友列表
        {
            qDebug()<<"somechat(*buf == '1')";
            emit sigAddFriend(rec_mes.getRevMessage());
        }
        else if(*buf == '2')//收到的为好友聊天信息，加入窗口聊天框
        {
            qDebug()<<"555,somechat";
           // udpsocket->writeDatagram("send_mes", 10,sender_ip, 50001);
            emit sigRevText(rec_mes.getRevText(),sender_ip);
        }

        else if(*buf == '3')//收到下线广播
        {
            qDebug()<<"someclosed(*buf == '-1')";
            emit sigClosed(sender_ip.toString());
        }
        rec_mes.cleanRev();
     }
}

