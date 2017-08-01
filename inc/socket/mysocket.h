#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QUdpSocket>
#include "udpmessage.h"

class Mysocket : public QObject
{
    Q_OBJECT
public:
    explicit Mysocket(QObject *parent = 0);

signals:
    void sigAddFriend(userMessage* user);
    void sigRevText(QString str,QHostAddress ipipaddr);

public slots:
    void recMessage();
    void sendMessage(QHostAddress ipaddr, QString str);

private:
    int flag;
    QUdpSocket *udpsocket;
    udpmessage send_mes;
    udpmessage rec_mes;
};

#endif // MYSOCKET_H
