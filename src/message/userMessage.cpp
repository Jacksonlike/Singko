#include <userMessage.h>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QHostInfo>
#include <QString>

userMessage::userMessage(QObject *parent) : Message(parent)
{
    this->groupnum = 0;
}

userMessage::userMessage(QString IP, QObject *parent) : Message(parent)
{
    this->groupnum = 0;
    setIP(IP);
}

userMessage::~userMessage()
{
    Writefile();
}

//私有函数
void userMessage::Readfile()
{
    //读取用户配置信息
    QString path = QCoreApplication::applicationDirPath()
                    + QString("/userlist/") + getIP();

    QFile file(path + QString("/config"));
    if (!file.exists())
    {
        this->Writefile();
        return;
    }

#ifdef DEBUG_USERMESSAGE
    if( !file.open(QIODevice::ReadOnly) )
        qDebug() << "usrMessage::Readfile(),file open failed !";
#else
    file.open(QIODevice::ReadOnly);
#endif

    QString line;
    while(!file.atEnd())
    {
        line = file.readLine();
        QStringList list = line.split("=");
        if (list[0] == "group_num")
            this->setGroup(list[1].toInt());
        if (list[0] == "headprotrait_num")
            this->setHeadprotrait(list[1].toInt());
        if (list[0] == "username")
            this->setName(list[1].remove("\n"));
        if (list[0] == "signature")
            this->setSignature(list[1].remove("\n"));
        if (list[0] == "hostname")
            this->setHostname(list[1].remove("\n"));
    }
    file.close();

#ifdef DEBUG_USERMESSAGE
    qDebug() << "application'path :  " << path;
    qDebug() << "group_num        :  " << getGroup();
    qDebug() << "headprotrait_num :  " << getHeadprotrait();
    qDebug() << "usrname          :  " << getName();
    qDebug() << "signature        :  " << getSignature();
    qDebug() << "my ip addresses  :  " << getIP();
    qDebug() << "my host name     :  " << getHostname();
#endif
}

void userMessage::Writefile()
{
    QString path = QCoreApplication::applicationDirPath()
                    + QString("/userlist/");

   QDir(path).mkpath(getIP());

    path += getIP();
    QFile file(path + QString("/config"));

#ifdef DEBUG_USERMESSAGE
    if( !file.open(QIODevice::WriteOnly) )
        qDebug() << "userMessage::Writefile(),file open failed !";
#else
    file.open(QIODevice::WriteOnly);
#endif

    QTextStream out(&file);
    out << "group_num="   << QString("%1").arg(getGroup()) << endl;
    out << "headprotrait_num=" << QString("%1").arg(getHeadprotrait()) << endl;
    out << "username="  << getName() << endl;
    out << "signature=" << getSignature() << endl;
    out << "hostname="  << getHostname()  <<endl;
    file.close();

#ifdef DEBUG_USERMESSAGE
    Readfile();
#endif
}
