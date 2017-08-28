#ifndef FRIEND_PUSHBUTTON_H
#define FRIEND_PUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include "userMessage.h"
#include <QHostAddress>
#include "chatwindow.h"
#include <QTimer>


class FriendPushbutton:public QPushButton
{
    Q_OBJECT
public:
    FriendPushbutton(userMessage* u, QWidget *parent = 0);
    ~FriendPushbutton();
    void setdefaultStytle();
    void settwinkleStytle();

    inline int  getFlag();
    inline void setFlag(int n);
    inline userMessage * getUser();



public slots:

    void revFriendMessage(QString str, QHostAddress ipaddr);
    void mousePressEvent(QMouseEvent * event);
    void buttonTwinkle();
    void closeWindow();

signals:
    void sigButtonMessage(QString str);

private:
    userMessage *user;
    int push_flag;
    QTimer twinkle;
    QString friendmessage;
};


inline void FriendPushbutton::setFlag(int n)
{
    push_flag = n;
}

inline userMessage *FriendPushbutton::getUser()
{
    return user;
}

inline int FriendPushbutton::getFlag()
{
    return push_flag;
}

#endif // FRIEND_PUSHBUTTON_H
