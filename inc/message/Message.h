#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

//==============================================================
/*                        message
** 用户信息的基类，包含两个子类，分别是本机的个人信息，和其他用户的相关信
** 息，不可创建对象。
** IP地址是对每一个用户唯一的标识，IP确认，则自动调用读取文件获取其他信息
** 的操作
*/
//==============================================================

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = 0);

    inline QString getName();
    inline QString getSignature();
    inline QString getIP();
    inline QString getHostname();
    inline int  getHeadprotrait();
    inline void setName(QString name);

    inline void setHostname(QString hostname);
    inline void setHeadprotrait(int num);
    void setIP(QString IP);

signals:
    void NameChanged(QString name);
    void SignatureChanged(QString sig);
    void HostnameChanged(QString hostname);
    void HeadprotraitChanged(int num);

public slots:
    inline void setSignature(QString sig);
private:
    virtual void Readfile()  = 0;
    virtual void Writefile() = 0;
    int headprotrait;
    QString usrname;
    QString hostname;
    QString signature;
    QString userIP;
};

inline QString Message::getName()
{
    return this->usrname;
}

inline void Message::setName(QString name)
{
    this->usrname = name;
    emit NameChanged(name);
}

inline QString Message::getSignature()
{
    return this->signature;
}

inline void Message::setSignature(QString sig)
{
    this->signature = sig;
    emit SignatureChanged(sig);
}

inline QString Message::getIP()
{
    return this->userIP;
}

inline int Message::getHeadprotrait()
{
    return this->headprotrait;
}

inline QString Message::getHostname()
{
    return this->hostname;
}

inline void Message::setHostname(QString hostname)
{
    this->hostname = hostname;
    emit HostnameChanged(hostname);
}

inline void Message::setHeadprotrait(int num)
{
    this->headprotrait = num;
    emit HeadprotraitChanged(num);
}

#endif // MESSAGE_H
