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

    connect(mSysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));

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
    //=======界面吸附属性的设置========
    EdgeHideTime = 10;
    EdgeMoveTime = 10;
    timer_Hide = new QTimer(this);
    timer_Show = new QTimer(this);
    timer_Inter= new QTimer(this);
    timer_Inter->setInterval(3000);
    timer_Hide->setInterval(EdgeMoveTime);//自己设定一个间断的时间
    timer_Show->setInterval(EdgeHideTime);//自己设定一个间断的时间
    connect(timer_Hide,SIGNAL(timeout()),this,SLOT(updateHide()));
    connect(timer_Show,SIGNAL(timeout()),this,SLOT(updateShow()));
    connect(timer_Inter,SIGNAL(timeout()),this,SLOT(updateInter()));
    timer_Hide->start();
    //=====================
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

    ui->close_pushbutton->setStyleSheet("QPushButton{background-color:transparent}\
                                        QPushButton:hover{background:qlineargradient"
                                                          "(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                                                          "stop:0 rgba(180,0,0,150),"
                                                          "stop:1 rgba(0,0,0,0));}");
    ui->mini_pushbutton->setStyleSheet("QPushButton{background-color:transparent}\
                                      QPushButton:hover{background:qlineargradient"
                                                        "(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                                                        "stop:0 rgba(165,200,200,150),"
                                                        "stop:1 rgba(0,0,0,0));}");
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
    this->Setting_Button->setIcon(p);
    this->Setting_Button->setIconSize(QSize(40, 40));
    this->Setting_Button->setGeometry(0, 600, 50, 50);

    p = QPixmap(QString(":/other/image/file.svg"));
    this->Sharing_Button->setIcon(p);
    this->Sharing_Button->setIconSize(QSize(20, 20));
    this->Sharing_Button->setGeometry(60, 620, 25, 25);

    p = QPixmap(QString(":/other/image/logo.ico"));
    this->About_Button->setIcon(p);
    this->About_Button->setIconSize(QSize(20, 20));
    this->About_Button->setGeometry(90, 620, 25, 25);
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
    qDebug() << "helo wolrd";
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
    int y = event->globalPos().ry()-this->pos().ry();
    this->dPos = event->globalPos()-this->pos(); // 移动后部件所在的位置
    mov = false;
    if( y > 0 && y < 35)
      mov = true;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(mov)
        this->move(event->globalPos()-this->dPos);
}

void Widget::on_mini_pushbutton_clicked()
{
    this->hide();
}

void Widget::on_close_pushbutton_clicked()
{
    QApplication::quit();
}

void Widget::updateHide()
{
    if( !HideOrNot() )
        return;
    int x = this->pos().rx();
    int y = this->pos().ry() - 100;
    y = y <= -550 ? -645 : y;
    move(x, y);
    if( y == -645 )
    {
        timer_Show->start();
        timer_Hide->stop();
    }
}

void Widget::updateShow()
{
    if( !ShowOrNot() )
        return;
    int x = this->pos().rx();
    int y = this->pos().ry() + 100;
    y = y >= -100 ? 0 : y;
    move(x, y);
    if( y == 0 )
    {
        timer_Show->stop();
        timer_Inter->start();
    }
}

void Widget::updateInter()
{
    if (!this->geometry().contains(QCursor::pos())) //判断鼠标是否在区域内
    {
        timer_Hide->start();
        timer_Inter->stop();
    }
}

bool Widget::HideOrNot()
{
    // 获取屏幕宽度
    if( this->pos().ry() < 10 )
        return true;
    else
        return false;
}

bool Widget::ShowOrNot()
{
    int x  = QCursor::pos().rx();
    int y  = QCursor::pos().ry();
    int sx = this->pos().rx();
    if( y<=5 && x>=sx && x<=(sx+300) )
        return true;
    else
        return false;
}



void Widget::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
   switch(reason)
   {
   //点击托盘显示窗口
   case QSystemTrayIcon::Trigger:
   {
        break;
   }
   //双击托盘显示窗口
   case QSystemTrayIcon::DoubleClick:
   {
        timer_Show->start();
        timer_Hide->stop();
        timer_Inter->stop();
        break;
   }
   default:
        break;
   }
}
