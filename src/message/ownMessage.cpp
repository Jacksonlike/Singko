#include <ownMessage.h>
#include <QFile>
#include <QCoreApplication>
#include <QHostInfo>
#include <QString>

ownMessage::ownMessage(QObject *parent) : Message(parent)
{
    this->background = 1;
    this->setHostname(QHostInfo::localHostName());
    this->setIP(getLocalIP());
}

void ownMessage::setBackground(int back)
{
    this->background = back;
}

int ownMessage::getBackground()
{
    return this->background;
}

QString ownMessage::getLocalIP()
{
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress addr, info.addresses())
    {
        if(addr.protocol() == QAbstractSocket::IPv4Protocol
                && addr.toString().contains("192.168.1."))
            return addr.toString();
    }
    return NULL;
}

//以下是私有函数
void ownMessage::Readfile()
{
    //读取用户配置信息
    QString path = QCoreApplication::applicationDirPath();
    QFile file(path + QString("/config"));
    if (!file.exists())
    {
        this->Writefile();
        return;
    }

#ifdef DEBUG_OWNMESSAGE
    if( !file.open(QIODevice::ReadOnly) )
        qDebug() << "ownMessage::Readfile(),file open failed !";
#else
    file.open(QIODevice::ReadOnly);
#endif

    QString line;
    while(!file.atEnd())
    {
        line = file.readLine();
        QStringList list = line.split("=");
        if (list[0] == "background_num")
            this->setBackground(list[1].toInt());
        if (list[0] == "headprotrait_num")
            this->setHeadprotrait(list[1].toInt());
        if (list[0] == "username")
            this->setName(list[1].remove("\n"));
        if (list[0] == "signature")
            this->setSignature(list[1].remove("\n"));
//        if (list[0] == "group")
//            this->group.append(list[1].remove("\n"));
    }
    file.close();

#ifdef DEBUG_OWNMESSAGE
    qDebug() << "application'path :  " << path;
    qDebug() << "background_num   :  " << getBackground();
    qDebug() << "headprotrait_num :  " << getHeadprotrait();
    qDebug() << "usrname          :  " << getName();
    qDebug() << "signature        :  " << getSignature();
    qDebug() << "my ip addresses  :  " << getIP();
    qDebug() << "group            :  " << group;
#endif
}

void ownMessage::Writefile()
{
    QString path = QCoreApplication::applicationDirPath();
    QFile file(path + QString("/config"));

#ifdef DEBUG_OWNMESSAGE
    if( !file.open(QIODevice::WriteOnly) )
        qDebug() << "ownMessage::Writefile(),file open failed !";
#else
    file.open(QIODevice::WriteOnly);
#endif

    QTextStream out(&file);
    out << "background_num="   << QString("%1").arg(getBackground())   << endl;
    out << "headprotrait_num=" << QString("%1").arg(getHeadprotrait()) << endl;
    out << "username="  << getName() << endl;
    out << "signature=" << getSignature() << endl;
    file.close();

#ifdef DEBUG_OWNMESSAGE
    Readfile();
#endif
}

