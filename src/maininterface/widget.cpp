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
    this->display();
    //好友列表（第一个列表）
    this->usrlist = new Toolbox(ui->tabWidget->widget(0));
    this->usrlist->setFixedSize(QSize(width(), height()-120));
}

void Widget::display()
{
    setWindowIcon(QIcon(":/other/image/logo.ico"));
    ui->search_icon->setIcon(QIcon(":/other/image/Magnifier.svg"));

    QPalette pa;
    pa.setColor(QPalette::Text, Qt::darkGray);
    ui->search_bar->setPalette(pa);
    ui->search_bar->setText("Search your friends...");

    this->setBackground(master->getBackground());
    this->setHeadprotrait(master->getBackground());
    this->setUsrname(master->getName());
    this->setSignature(master->getSignature());
}

Widget::~Widget()
{
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
    ui->head->setIconSize(QSize(60, 60));
}

void Widget::setUsrname(QString name)
{
    ui->usr_name->setText(name);
}

void Widget::setSignature(QString signature)
{
    ui->signature->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
    if(signature.isEmpty())
    {
        QPalette pa;
        pa.setColor(QPalette::Text, Qt::darkGray);
        ui->signature->setPalette(pa);
        ui->signature->setText(QString("Please input your personalized signature!"));
    }
    else
        ui->signature->setText(signature);
}
