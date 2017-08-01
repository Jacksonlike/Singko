#include <toolbox.h>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include "friend_pushbutton.h"
#include "mysocket.h"

extern Mysocket *myudp_socket;
Toolbox::Toolbox(QWidget *parent) : QToolBox(parent)
{
    this->Readfile();
    //=================
    userMessage *a = new userMessage("192.168.1.127");
    userMessage *b = new userMessage("192.168.1.128");
    addContacts(a);
    addContacts(b);

    connect(myudp_socket, SIGNAL(sig_add_friend(userMessage*)),this,SLOT(addContacts(userMessage*)));
    //=================
}

void Toolbox::addContacts(userMessage *someone)
{
    this->OnlineContects.append(someone);

    QIcon p = QPixmap(QString(":/default_head%1.jpg").arg(someone->getHeadprotrait()));
    Friend_Pushbutton *button = new
            Friend_Pushbutton(someone,this);

    button->resize(QSize(300, 50));
    button->move(0,this->OnlineContects.count()*50);
    button->setStyleSheet("text-align: left;");//左对齐

    button->setText(someone->getName()+someone->getSignature());

    button->setIcon(p);
    button->setIconSize(QSize(35, 35));


    connect(button, SIGNAL(clicked(bool)),button,
             SLOT(on_pushButton_clicked()));
    connect(myudp_socket, SIGNAL(sig_rev_text(QString,QHostAddress)),
            button,SLOT(rev_friend_message(QString,QHostAddress)));
}

void Toolbox::deleteContacts(userMessage *someone)
{
    this->OnlineContects.removeAll(someone);

    delete someone;
}

//私有函数
void Toolbox::Readfile()
{
    //读取用户配置信息
    QString path = QCoreApplication::applicationDirPath()
                    + QString("/userlist/");

    QFile file(path + QString("/config"));
    if (!file.exists())
    {
        this->Writefile();
        return;
    }

#ifdef DEBUG_TOOLBOX
    if( !file.open(QIODevice::ReadOnly) )
        qDebug() << "usrMessage::Readfile(),file open failed !";
#else
    file.open(QIODevice::ReadOnly);
#endif

    friendlist.clear();
    QString line;
    while(!file.atEnd())
    {
        line = file.readLine();
        QStringList list = line.split("=");
        this->friendlist.insert(list[0].toInt()
                , list[1].remove("\n").remove("\r"));
    }
    file.close();

#ifdef DEBUG_TOOLBOX
    qDebug() << "application'path :  " << path;
    qDebug() << "group_num        :  " << friendlist;

#endif
}

void Toolbox::Writefile()
{
    QString path = QCoreApplication::applicationDirPath()
                    + QString("/userlist/");

    QDir dir;
    if ( !dir.exists(path) )
        dir.mkdir(path);

    QFile file(path + QString("/config"));

#ifdef DEBUG_TOOLBOX
    if( !file.open(QIODevice::WriteOnly) )
        qDebug() << "Toolbox::Writefile(),file open failed !";
#else
    file.open(QIODevice::WriteOnly);
#endif

    QTextStream out(&file);
    if (friendlist.empty())
        friendlist.insert(0, "My Friends");

    QMap <int, QString>::iterator it;
    for (it=friendlist.begin(); it!=friendlist.end(); it++)
    {
        out << it.key() << "=" << it.value();
    }

    file.close();

#ifdef DEBUG_TOOLBOX
    Readfile();
#endif
}
