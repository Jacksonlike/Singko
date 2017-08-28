#include "udpmessage.h"
#include <QtDebug>

udpmessage::udpmessage(QObject *parent) : QObject(parent)
{
    revText.clear();
    sendText.clear();
}

void udpmessage::setRevText(char *ch)
{
    if(*ch == '0' || *ch == '1') //收到的为上线广播或者好友信息
    {
        char *p = ch;
        QString mes[6];
        qint16 i = 0;
        while(*p != '\0')
        {
            if(*p != '^')
                mes[i] += *p;
            if(*p == '^')
                i++;
            p++;
        }

        revMessage = new userMessage;
        revMessage->setHeadprotrait(mes[1].toInt());
        revMessage->setName(mes[2]);
        revMessage->setHostname(mes[3]);
        revMessage->setSignature(mes[4]);
        revMessage->setIP(mes[5]);
    }
    else if(*ch == '2') //收到的为普通消息
    {
        revText = ch+2;
    }
}

void udpmessage::setSendText(int label, ownMessage *mes)
{
    //标记位+'^'+个人信息
    QString str = QString("%1^%2").arg(f).arg(mes->getHeadprotrait())
            +"^"+mes->getName()+"^"+mes->getHostname()+"^"
           +mes->getSignature()+"^"+mes->getIP();
    sendText = sendText.append(str);

}

void udpmessage::setSendText(int label, QString str)
{
    //标记位+'^'+内容
    sendText = sendText.append(QString("%1").arg(label));
    sendText = sendText.append('^');
    sendText = sendText.append(str);
}

