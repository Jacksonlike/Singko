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

    QString getName();
    QString getSignature();
    QString getIP();
    QString getHostname();
    int  getHeadprotrait();
    void setName(QString name);
    void setSignature(QString sig);
    void setHostname(QString hostname);
    void setHeadprotrait(int num);
    void setIP(QString IP);
    virtual void Readfile()  = 0;
    virtual void Writefile() = 0;

signals:
    void NameChanged(QString name);
    void SignatureChanged(QString sig);
    void HostnameChanged(QString hostname);
    void HeadprotraitChanged(int num);

public slots:

private:
    int headprotrait;
    QString usrname;
    QString hostname;
    QString signature;
    QString userIP;
};

#endif // MESSAGE_H
