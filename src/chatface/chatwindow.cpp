#include "ui_chatwindow.h"
#include "expression.h"
#include "chatwindow.h"
#include "mysocket.h"
#include "widget.h"
#include <QDebug>
#include <QDir>
#include <QTextDocumentFragment>
#include <QColor>

extern Mysocket* myudp_socket;
ChatWindow::ChatWindow(QWidget *parent, userMessage * fri):
    QDialog(parent),
    ui(new Ui::ChatWindow),friendmessage(fri)
{
    ui->setupUi(this);
//    dPos = this->pos();
    init_button();
    mymessage = new ownMessage;
    myexpression = new expression(this);
    qDebug()<<fri->getIP();

    show_friendInformation(friendmessage);
    display();
}


void ChatWindow::init_button()
{
    ui->pushButton_video->setIcon(QIcon(QPixmap(":/other/image/vedio.ico")));
    ui->pushButton_video->setIconSize(QSize(28,28));
    ui->pushButton_video->setStyleSheet("border:none");
    ui->pushButton_video->setMouseTracking(true);
    ui->pushButton_voice->setIcon(QIcon(":/other/image/voice.ico"));
    ui->pushButton_voice->setIconSize(QSize(28,28));
    ui->pushButton_voice->setStyleSheet("border:none");

    ui->pushButton_sharefile->setIcon(QIcon(":/other/image/share.ico"));
    ui->pushButton_sharefile->setIconSize(QSize(28,28));
    ui->pushButton_sharefile->setStyleSheet("border:none");

    ui->pushButton_control->setIcon(QIcon(":/other/image/control.ico"));
    ui->pushButton_control->setIconSize(QSize(28,28));
    ui->pushButton_control->setStyleSheet("border:none");

    ui->pushButton_picture->setIcon(QIcon(":/other/image/picture.ico"));
    ui->pushButton_picture->setIconSize(QSize(20,20));

    ui->pushButton_FaceExpression->setIcon(QIcon(":/other/image/FaceExpression.ico"));
    ui->pushButton_FaceExpression->setIconSize(QSize(20,20));

    ui->pushButton_font->setIcon(QIcon(":/other/image/font.ico"));
    ui->pushButton_font->setIconSize(QSize(20,20));
}


void ChatWindow::show_friendInformation(userMessage* friendMessage)
{
   ui->textBrowser_friendInformation->append("Username："+friendMessage->getName());
   ui->textBrowser_friendInformation->append("Hostname："+friendMessage->getHostname());
   ui->textBrowser_friendInformation->append("Signature: "+friendMessage->getSignature());
   ui->textBrowser_friendInformation->append("Ipaddress: "+friendMessage->getIP());
   ui->label_username->setText(friendMessage->getName());
   QString headimagename =QString(":/head/head/default_head%1.jpg")
           .arg(friendMessage->getHeadprotrait());
   ui->pushButton_headimage->setIcon(QIcon(headimagename));
   ui->pushButton_headimage->setIconSize(QSize(25,25));

}


ChatWindow::~ChatWindow()
{
    delete myexpression;
    delete mymessage;
    delete ui;
}

void ChatWindow::on_pushButton_FaceExpression_clicked()
{
    myexpression->show();
   // myexpression->exec();
}

void ChatWindow::slots_expression_clicked(QTableWidgetItem* Item)
{

    int num = Item->row()*8 + Item->column();
    QDir *expression_dir = new QDir(":/face/face/");
    QStringList myexpression_list = expression_dir->entryList();//文件名列表
    QList<QString>::iterator i = myexpression_list.begin();
    i+=num;
    QString filename(":/face/face/"+*i);
    QTextImageFormat imageFormat;   //保存图片格式对象
    imageFormat.setName(filename);
    imageFormat.setHeight(20);
    imageFormat.setWidth(20);

    //获取当前光标
    QTextCursor cursor = ui->textEdit_sendmessage->textCursor();
    cursor.insertImage(imageFormat);

    myexpression->close();
    delete expression_dir;
}

void ChatWindow::on_pushButton_2_clicked()//发送聊天消息，并更新自己界面
{

    ui->textBrowser_ChatLog->setTextColor(QColor(255,0,0));
    ui->textBrowser_ChatLog->setFontPointSize(12);
    QString text = ui->textEdit_sendmessage->toHtml();
    qDebug() << text;
    if (text.isEmpty())
        return;
    ui->textBrowser_ChatLog->append(mymessage->getName()+":");
    ui->textBrowser_ChatLog->append(text);
    myudp_socket->sendMessage(QHostAddress(friendmessage->getIP()),
                              ui->textEdit_sendmessage->toHtml());
    ui->textEdit_sendmessage->clear();
}

void ChatWindow::on_pushButton_clicked()
{
    delete this;
}

void ChatWindow::slot_button_message(QString str)
{
    ui->textBrowser_ChatLog->setTextColor(QColor(0,255,0));
    ui->textBrowser_ChatLog->setFontPointSize(12);
    ui->textBrowser_ChatLog->append(friendmessage->getName()+":");
    ui->textBrowser_ChatLog->append(str);
}


void ChatWindow::on_mini_pushbutton_clicked()
{
    this->showMinimized();
}

void ChatWindow::on_close_pushbutton_clicked()
{
    delete this;
}

void ChatWindow::mousePressEvent(QMouseEvent *event)
{
    int y = event->globalPos().ry()-this->pos().ry();
    this->dPos = event->globalPos()-this->pos(); // 移动后部件所在的位置
    mov = false;
    if( y > 0 && y < 20)
        mov = true;
}

void ChatWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mov)
        this->move(event->globalPos()-this->dPos);
}

void ChatWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        on_pushButton_2_clicked();
    if (event->key() == Qt::Key_Escape)
        delete this;
    else
        QDialog::keyPressEvent(event);
}

void ChatWindow::display()
{
    setWindowIcon(QIcon(":/other/image/logo.ico"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    //按钮格式设置
    ui->close_pushbutton->setStyleSheet("QPushButton{background-color:transparent}"
                                      "QPushButton:hover{background:qlineargradient"
                                      "(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                                      "stop:0 rgba(250,0,0,150),"
                                      "stop:1 rgba(0,0,0,0));}");
    ui->mini_pushbutton->setStyleSheet("QPushButton{background-color:transparent}"
                                      "QPushButton:hover{background:qlineargradient"
                                      "(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                                      "stop:0 rgba(0,0,0,50),"
                                      "stop:1 rgba(0,0,0,0));}");
    this->setWindowTitle(friendmessage->getName());
}


