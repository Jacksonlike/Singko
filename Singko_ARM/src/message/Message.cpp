#include <Message.h>

Message::Message(QObject *parent) : QObject(parent)
{
    this->signature.clear();
    this->headprotrait = 1;
    this->usrname = "Jack";
}

void Message::setIP(QString IP)
{
    this->userIP = IP;
    Readfile();
}
