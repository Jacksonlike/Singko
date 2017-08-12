#include <toolbox.h>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <mysocket.h>

extern Mysocket *myudp_socket;
Toolbox::Toolbox(QWidget *parent) : QToolBox(parent)
{
    usrtable.clear();
    this->Readfile();

    connect(myudp_socket, SIGNAL(sigAddFriend(userMessage *)),
                        this, SLOT(addContacts(userMessage *)));
    connect(myudp_socket, SIGNAL(sigClosed(QString)),
                        this, SLOT(deleteContacts(QString)));
    //与Socket增加好友的信号连接
}

Toolbox::~Toolbox()
{
    Writefile();
}

void Toolbox::addContacts(userMessage *someone)
{
    qDebug()<<"addcontacts!";
    //判断是否已经添加该用户
    quint32 IPnum = QHostAddress(someone->getIP()).toIPv4Address();
    QMap<quint32, FriendPushbutton *>::const_iterator its = usrtable.find(IPnum);
    if (its != usrtable.end())
    {
        qDebug()<<someone->getIP()<<" had onlion";
        return;
    }


    QMap <int, GroupWidget *>::const_iterator it
                    = friendlist.find(someone->getGroup());

    if (it == friendlist.end())
    {
        someone->setGroup(0);
        it = friendlist.find(0);
    }

    FriendPushbutton *button = new
            FriendPushbutton(someone, it.value()->getWidget());


    QIcon p = QPixmap(QString(":/head/head/default_head%1.jpg")
                                .arg(someone->getHeadprotrait()));
    button->resize(QSize(300, 50));
    button->move(0, it.value()->count()*50);
    button->setStyleSheet("text-align: left;");

    button->setText(someone->getName()+someone->getSignature());
    button->setIcon(p);
    button->setIconSize(QSize(35, 35));

    connect(myudp_socket, SIGNAL(sigRevText(QString,QHostAddress)),
            button,SLOT(revFriendMessage(QString,QHostAddress)));

    it.value()->countplus();                //对应的分组里面的人数增加一人
    it.value()->Buttonlist.append(button);  //对应分组里面的按钮增加一个

    //将用户添加到usrtable进行管理
    this->usrtable.insert(IPnum, button);
    this->update();
}

void Toolbox::deleteContacts(QString IP)
{
    //判断用户是否存在
    quint32 IPnum = QHostAddress(IP).toIPv4Address();
    QMap<quint32, FriendPushbutton *>::const_iterator it = usrtable.find(IPnum);

    if (it == usrtable.end())
        return;

    userMessage *u = it.value()->getUser();
    QMap <int, GroupWidget *>::const_iterator its
                    = friendlist.find(u->getGroup());
    QList<FriendPushbutton *> list = its.value()->Buttonlist;

    its.value()->countreduce();//对应分组人数减少
    list.removeOne(it.value());

    delete it.value();      //析构已删除的按钮和设置对应联系人下线
    usrtable.remove(IPnum); //删除联系人列表中对应人

    //刷新该分组列表
    FriendPushbutton *p;
    int i = 0;
    foreach (p, list)
    {
        p->move(0, i*50);
        i++;
    }

#ifdef DEBUG_TOOLBOX
    qDebug() << "==DEBUG_TOOLBOX==";
    for (it=usrtable.begin(); it!=usrtable.end(); it++)
    {
        qDebug() << "IPnum : " << it.key();
    }
    qDebug() << "=================";
#endif
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
        GroupWidget *widget = new GroupWidget(this);
        widget->setTitle(list[1].remove("\n").remove("\r"));
        this->addItem(widget->getWidget(), widget->getTitle());
        this->friendlist.insert(list[0].toInt(), widget);
    }
    file.close();
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
    {
        GroupWidget *widget = new GroupWidget(this);
        widget->setTitle("My Friend");
        this->friendlist.insert(0, widget);
    }

    QMap <int, GroupWidget *>::iterator it;
    for (it=friendlist.begin(); it!=friendlist.end(); it++)
    {
        out << it.key() << "=" << it.value()->getTitle() << "\n";
    }

    file.close();
}
