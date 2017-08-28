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
    this->usrlist = new Toolbox(ui->tabWidget->widget(0));
    this->Setting_Button = new MyPushbutton(this);
    this->Sharing_Button = new MyPushbutton(this);
    this->display();

    //==============
//    userMessage *someone = new userMessage("127.0.0.1");
//    someone->setName("meimie");
//    someone->setGroup(2);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.127");
//    someone->setGroup(1);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.120");
//    someone->setGroup(0);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.122");
//    someone->setGroup(0);
//    usrlist->addContacts(someone);
    //===============
}

void Widget::display()
{
    this->setGeometry(0,0,300,480);
    this->setWindowFlags(Qt::FramelessWindowHint);  //去除widget边框
//    setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);

    ui->tabWidget->setTabIcon(0, QIcon(":/other/image/contact.svg"));
    ui->tabWidget->setTabIcon(1, QIcon(":/other/image/contacts.svg"));
    ui->tabWidget->setTabIcon(2, QIcon(":/other/image/recentcontact.svg"));
    ui->tabWidget->setStyleSheet("font-size : 7pt;QTabBar::tab{width:100px;}");

    ui->logo->setIcon(QIcon(":/other/image/logo.ico"));
    ui->logo->setIconSize(QSize(23,23));
    ui->logo->setStyleSheet("background-color:transparent");
    //设置背景图 用户名 头像
    this->setBackground(master->getBackground());
    this->setHeadprotrait(master->getBackground());
    this->setUsrname(master->getName());

    ui->close_pushbutton->setStyleSheet("QPushButton{border-radius: 5px;background-color:transparent}\
                                        QPushButton:hover{border-radius: 5px;background:qlineargradient"
                                                          "(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                                                          "stop:0 rgba(180,0,0,150),"
                                                          "stop:1 rgba(0,0,0,0));}");

    //好友列表（第一个列表）
    this->usrlist->setFixedSize(QSize(width(), height()-200));
}

Widget::~Widget()
{
    myudp_socket->setFlag(-1);
    myudp_socket->sendMessage(QHostAddress::Broadcast,"-1");//退出发送广播
    delete this->usrlist;
    delete this->master;
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
    ui->head->setIconSize(QSize(40 ,40));
}

void Widget::setUsrname(QString name)
{
    ui->usr_name->setText(name);
}

void Widget::on_close_pushbutton_clicked()
{
    QApplication::quit();
}




