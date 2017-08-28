#include "mytcp.h"
#include "ownMessage.h"
#include <QFile>
#include <QDebug>

Mytcp::Mytcp()
{
    tcpsocket = new QTcpSocket;
    tcpserver = new QTcpServer;
    tcpsocket->bind(QHostAddress(ownMessage::getLocalIP()),50002);
    if(!tcpserver->listen(QHostAddress::Any,50002))
    {
       qDebug()<<"listen error";

    }
    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(onNewconnection()));

}

void Mytcp::sendFile(QHostAddress ipaddr,QString filepath)
{
    QByteArray text;
    QString temp;
    text.append(filepath).append("^");//发送文件名
    qDebug()<<"textfirst : "<<text;
    tcpsocket->connectToHost(ipaddr,50002);//连接主机
    connect(tcpsocket,SIGNAL(connected()),this,SLOT(onConnected()));
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);
   // int file_size = file.size()+filepath.size(); //文件大小+文件名长度
    QTextStream in(&file);
    temp = in.readAll();
    text.append(temp);
    int n = tcpsocket->write(text);
    qDebug()<<"tcp ip :"<<ipaddr;
    qDebug()<<"text : "<<text;
    qDebug()<<"n = "<<n;
}
/*
void Mytcp::sendDir(QHostAddress ipaddr, QString dirname)
{

}
*/
void Mytcp::revFile()
{
    QString text = tcpsocket->readAll();
    QHostAddress addrip = QHostAddress(tcpsocket->peerAddress().toString().section(':',-1,-1));
    emit sigRevfile(addrip, text); //给窗口发信号
}

void Mytcp::revDir()
{

}

void Mytcp::onConnected()
{
    qDebug()<<"someone connected!";
}
void Mytcp::onNewconnection()
{
    qDebug()<<"onNewconnection";
    tcpsocket = tcpserver->nextPendingConnection();
    connect(tcpsocket,SIGNAL(readyRead()),this ,SLOT(revFile()));
}
