#ifndef FRIEND_PUSHBUTTON_H
#define FRIEND_PUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include "userMessage.h"
#include <QHostAddress>
#include "chatwindow.h"


class Friend_Pushbutton:public QPushButton
{
    Q_OBJECT
public:
    Friend_Pushbutton(userMessage* u, QWidget *parent = 0);
    int get_flag();
    void set_flag(int n);

public slots:
    void on_pushButton_clicked();
    void rev_friend_message(QString str, QHostAddress ipaddr);

signals:
    sig_button_message(QString str);

private:
    userMessage *user;
    int push_flag;


};

#endif // FRIEND_PUSHBUTTON_H
