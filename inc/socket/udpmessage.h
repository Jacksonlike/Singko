#ifndef UDPMESSAGE_H
#define UDPMESSAGE_H

#include <QObject>
#include "ownMessage.h"
#include "userMessage.h"


class udpmessage : public QObject
{
    Q_OBJECT
public:
    explicit udpmessage(QObject *parent = 0);

    void setSendText(int f,QString str);//普通消息
    void setSendText(int f,ownMessage *mes);//用户信息
    void cleanSend();
    QByteArray getSendText();

    void setRevText(char* ch);//普通消息
    void cleanRev();
    QString getRevText();
    userMessage* getRevMessage();

private:
    QString rev_text;
    userMessage *rev_message;
    QByteArray  send_text;
};

#endif // UDPMESSAGE_H
