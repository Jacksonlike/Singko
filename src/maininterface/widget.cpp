#include "widget.h"
#include "ui_maininterface.h"
#include <QMessageBox>

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

//    someone = new userMessage("192.168.1.125");
//    someone->setGroup(2);
//    someone->setName("hehe");
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.111");
//    someone->setGroup(1);
//    someone->setName("liuyang");
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.25");
//    someone->setGroup(1);
//    someone->setHeadprotrait(3);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.5");
//    someone->setGroup(1);
//    someone->setHeadprotrait(3);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.2");
//    someone->setGroup(1);
//    someone->setHeadprotrait(3);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.27");
//    someone->setGroup(2);
//    someone->setHeadprotrait(3);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.25");
//    someone->setGroup(2);
//    someone->setHeadprotrait(3);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.15");
//    someone->setGroup(1);
//    someone->setHeadprotrait(3);
//    usrlist->addContacts(someone);

//    someone = new userMessage("192.168.1.22");
//    someone->setGroup(5);
//    someone->setHeadprotrait(2);
//    usrlist->addContacts(someone);
//    usrlist->deleteContacts("192.168.1.111");
    //==============
}

void Widget::display()
{
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
    ui->Setting_Button->setStyleSheet("text-align: center;");
    ui->Setting_Button->setIcon(p);
    ui->Setting_Button->setIconSize(QSize(20, 20));

    p = QPixmap(QString(":/other/image/file.svg"));
    ui->Sharing_Button->setStyleSheet("text-align: center;");
    ui->Sharing_Button->setIcon(p);
    ui->Sharing_Button->setIconSize(QSize(20, 20));

    p = QPixmap(QString(":/other/image/logo.ico"));
    ui->About_Button->setStyleSheet("text-align: center;");
    ui->About_Button->setIcon(p);
    ui->About_Button->setIconSize(QSize(20, 20));

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
