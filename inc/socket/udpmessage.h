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

    void setSendText(int label,QString str);//普通消息
    void setSendText(int label, ownMessage *mes);//用户信息
    void setRevText(char* ch);//普通消息
    inline void cleanSend();
    inline void cleanRev();

    inline QString getRevText();
    inline QByteArray getSendText();
    inline userMessage* getRevMessage();

private:
    QString revText;
    QByteArray  sendText;
    userMessage *revMessage;
};

inline void udpmessage::cleanRev()
{
    revText.clear();
}

inline QByteArray udpmessage::getSendText()
{
    return sendText;
}

inline void udpmessage::cleanSend()
{
    sendText.clear();
}

inline QString udpmessage::getRevText()
{
    return revText;
}

inline userMessage* udpmessage::getRevMessage()
{
    return revMessage;
}
#endif // UDPMESSAGE_H
