#include "udpmessage.h"

udpmessage::udpmessage(QObject *parent) : QObject(parent)
{
    rev_text.clear();
    send_text.clear();
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
            {
                i++;
            }
            p++;
        }
        rev_message = new userMessage;
        rev_message->setHeadprotrait(mes[1].toInt());
        rev_message->setName(mes[2]);
        rev_message->setHostname(mes[3]);
        rev_message->setSignature(mes[4]);
        rev_message->setIP(mes[5]);
    }
    else if(*ch == '2') //收到的为普通消息
    {
        rev_text = ch+2;
    }
}

void udpmessage::cleanRev()
{
    rev_text.clear();
}

QByteArray udpmessage::getSendText()
{
    return send_text;
}

void udpmessage::cleanSend()
{
    send_text.clear();
}

QString udpmessage::getRevText()
{
    return rev_text;
}

userMessage* udpmessage::getRevMessage()
{
    return rev_message;
}


void udpmessage::setSendText(int f,ownMessage *mes)
{
    //标记位+'^'+个人信息
    QString str = QString("%1^%2").arg(f).arg(mes->getHeadprotrait())
            +"^"+mes->getName()+"^"+mes->getHostname()+"^"
           +mes->getSignature()+"^"+mes->getIP();
    send_text = send_text.append(str);

}

void udpmessage::setSendText(int f,QString str)
{
    //标记位+'^'+内容
    send_text = send_text.append(QString("%1").arg(f));
    send_text = send_text.append('^');
    send_text = send_text.append(str);
}

