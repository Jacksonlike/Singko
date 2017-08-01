#include <Message.h>

Message::Message(QObject *parent) : QObject(parent)
{
    this->signature.clear();
    this->headprotrait = 1;
    this->usrname = "Jack";
}


QString Message::getName()
{
    return this->usrname;
}

void Message::setName(QString name)
{
    this->usrname = name;
    emit NameChanged(name);
}

QString Message::getSignature()
{
    return this->signature;
}

void Message::setSignature(QString sig)
{
    this->signature = sig;
    emit SignatureChanged(sig);
}

QString Message::getIP()
{
    return this->userIP;
}

int Message::getHeadprotrait()
{
    return this->headprotrait;
}

QString Message::getHostname()
{
    return this->hostname;
}

void Message::setHostname(QString hostname)
{
    this->hostname = hostname;
    emit HostnameChanged(hostname);
}

void Message::setHeadprotrait(int num)
{
    this->headprotrait = num;
    emit HeadprotraitChanged(num);
}

void Message::setIP(QString IP)
{
    this->userIP = IP;
    Readfile();
}
