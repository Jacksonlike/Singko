#include "widget.h"
#include "ui_maininterface.h"


extern Mysocket *myudp_socket;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    myudp_socket->sendMessage(QHostAddress::Broadcast,0);//上线就广播

    ui->setupUi(this);
    this->master = new ownMessage;
    this->signature = new LineEdit(this);
    this->usrlist = new Toolbox(ui->tabWidget->widget(0));
    this->Setting_Button = new MyPushbutton(this);
    this->Sharing_Button = new MyPushbutton(this);
    this->About_Button   = new MyPushbutton(this);
    this->dPos = this->pos();

    connect(About_Button, SIGNAL(clicked()), this, SLOT(on_About_Button_clicked()));

    //新建QSystemTrayIcon对象
    mSysTrayIcon = new QSystemTrayIcon(this);

    this->display();

    //==============
    userMessage *someone = new userMessage("127.0.0.1");
    someone->setName("meimie");
    someone->setGroup(2);
    usrlist->addContacts(someone);

    someone = new userMessage("192.168.1.127");
    someone->setGroup(1);
    usrlist->addContacts(someone);

    someone = new userMessage("192.168.1.120");
    someone->setGroup(0);
    usrlist->addContacts(someone);

    someone = new userMessage("192.168.1.122");
    someone->setGroup(0);
    usrlist->addContacts(someone);
    //===============
}

void Widget::display()
{
    //新建托盘要显示的icon
    QIcon icon = QIcon(":/other/image/logo.ico");
    //将icon设到QSystemTrayIcon对象中
    mSysTrayIcon->setIcon(icon);
    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    mSysTrayIcon->setToolTip(QObject::trUtf8("Singko is online!"));
    //在系统托盘显示此对象
    mSysTrayIcon->show();
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,
            SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    //this->setWindowFlags(Qt::FramelessWindowHint);  //去除widget边框
    setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);

    ui->tabWidget->setTabIcon(0, QIcon(":/other/image/contact.svg"));
    ui->tabWidget->setTabIcon(1, QIcon(":/other/image/contacts.svg"));
    ui->tabWidget->setTabIcon(2, QIcon(":/other/image/recentcontact.svg"));
    ui->tabWidget->setStyleSheet("QTabBar::tab{width:100px;}");

    ui->close_pushbutton->setStyleSheet("background-color:transparent");
    ui->mini_pushbutton->setStyleSheet("background-color:transparent");
    //设置Logo
    setWindowIcon(QIcon(":/other/image/logo.ico"));
    ui->search_icon->setIcon(QIcon(":/other/image/Magnifier.svg"));

    //设置搜索条
    QPalette pa;
    pa.setColor(QPalette::Text, Qt::darkGray);
    ui->search_bar->setPalette(pa);
    ui->search_bar->setText("Search your friends...");

    //设置背景图 用户名 头像
    this->setBackground(master->getBackground());
    this->setHeadprotrait(master->getBackground());
    this->setUsrname(master->getName());

    //设置个性签名
    this->setSignature(master->getSignature());
    connect(signature, SIGNAL(textEdited(QString)), master, SLOT(setSignature(QString)));

    //设置三个底部按钮
    QIcon p = QPixmap(QString(":/other/image/syssetting.svg"));
    this->Setting_Button->setStyleSheet("text-align: center;"
                                      "background-color:transparent");
    this->Setting_Button->setIcon(p);
    this->Setting_Button->setIconSize(QSize(40, 40));

    p = QPixmap(QString(":/other/image/file.svg"));
    this->Sharing_Button->setStyleSheet("text-align: center;"
                                      "background-color:transparent");
    this->Sharing_Button->setIcon(p);
    this->Sharing_Button->setIconSize(QSize(20, 20));

    p = QPixmap(QString(":/other/image/logo.ico"));
    this->About_Button->setStyleSheet("text-align: center;"
                                    "background-color:transparent");
    this->About_Button->setIcon(p);
    this->About_Button->setIconSize(QSize(20, 20));

    //好友列表（第一个列表）
    this->usrlist->setFixedSize(QSize(width(), height()-200));
}

Widget::~Widget()
{
    myudp_socket->setFlag(-1);
    myudp_socket->sendMessage(QHostAddress::Broadcast,"-1");//退出发送广播
    delete this->usrlist;
    delete this->master;
    delete this->signature;
    delete ui;
}

void Widget::setBackground(int num)
{
    QPalette pal;
    QPixmap pic = QPixmap(QString(":/background/backgroound/default_background%1.jpg").arg(num));
    pic = pic.scaled(width(), height());

#ifdef DEBUG_WIDTH
    qDebug() << "width = " << width();
    qDebug() << "pic width = " << pic.width();
    qDebug() << "height = " << height();
    qDebug() << "pic height = " << pic.height();
#endif

    pal.setBrush(QPalette::Background, QBrush(pic));
    setPalette(pal);
}

void Widget::setHeadprotrait(int num)
{
    QIcon headprotrait = QPixmap(QString(":/head/head/default_head%1.jpg").arg(num));
    ui->head->setIcon(headprotrait);
    ui->head->setIconSize(QSize(60, 60));
}

void Widget::setUsrname(QString name)
{
    ui->usr_name->setText(name);
}

void Widget::setSignature(QString sig)
{
    signature->setGeometry(80, 50, 150, 20);
    if(sig.isEmpty())
    {
        signature->setText(QString("Please input your personalized signature!"));
    }
    else
        signature->setText(sig);
}

void Widget::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
       case QSystemTrayIcon::DoubleClick:
           this->show();
           break;
       default:
           break;
    }
}

void Widget::on_About_Button_clicked()              //显示About us信息
{
    QString text;
    text += QString("Author  : LiKe, LiuYang\n");
    text += QString("Date     : 2017-08-05\n");
    text += QString("Email    : jacksonlike290@gmail.com\n");
    text += QString("Version : 1.0");
    QMessageBox box(QMessageBox::Information, "About Singko", text,
                    QMessageBox::Ok, this);
    box.setIconPixmap(QString(":/other/image/logo.ico"));
    box.exec();
}

void Widget::mousePressEvent(QMouseEvent *event)
{ 
    this->dPos = event->globalPos() - this->pos(); // 移动后部件所在的位置
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
     this->move(event->globalPos() - this->dPos);
}

void Widget::on_mini_pushbutton_clicked()
{
    this->hide();
}

void Widget::on_close_pushbutton_clicked()
{
     QApplication::quit();
}
