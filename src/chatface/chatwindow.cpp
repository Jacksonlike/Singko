#include "ui_chatwindow.h"
#include <QDebug>
#include "expression.h"
#include <QDir>
#include<QTextDocumentFragment>
#include <QColor>
#include "chatwindow.h"
#include "mysocket.h"
#include "widget.h"

extern Mysocket* myudp_socket;
ChatWindow::ChatWindow(QDialog *parent,userMessage * fri):
    QDialog(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    init_button();
    mymessage = new ownMessage;
    qDebug()<<fri->getIP();
    friendmessage = new userMessage;
    friendmessage->setHeadprotrait(fri->getHeadprotrait());
    friendmessage->setHostname(fri->getHostname());
    friendmessage->setGroup(fri->getGroup());
    friendmessage->setIP(fri->getIP());
    friendmessage->setName(fri->getIP());
    friendmessage->setObjectName(fri->getName());
    //friendmessage = fri;
    myexpression = new expression(this);
    show_friendInformation(friendmessage);
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

    ui->pushButton_FaceExpression->setIcon(QIcon(":/FaceExpression.ico"));
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
   QString headimagename =QString(":/default_head%1.jpg").arg(friendMessage->getHeadprotrait());
   ui->pushButton_headimage->setIcon(QIcon(headimagename));
   ui->pushButton_headimage->setIconSize(QSize(45,45));

}


ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_pushButton_FaceExpression_clicked()
{
    myexpression->show();
    myexpression->exec();
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
}

void ChatWindow::on_pushButton_2_clicked()//发送聊天消息，并更新自己界面
{

    ui->textBrowser_ChatLog->setTextColor(QColor(255,0,0));
    ui->textBrowser_ChatLog->setFontPointSize(15);
    ui->textBrowser_ChatLog->append(mymessage->getName()+":");


    ui->textBrowser_ChatLog->append(ui->textEdit_sendmessage->toHtml());
    ui->textEdit_sendmessage->clear();

    myudp_socket->sendMessage(QHostAddress( friendmessage->getIP()),ui->textEdit_sendmessage->toHtml());
}

void ChatWindow::on_pushButton_clicked()
{
    this->close();
}

void ChatWindow::slot_button_message(QString str)
{
    ui->textBrowser_ChatLog->setTextColor(QColor(0,255,0));
    ui->textBrowser_ChatLog->setFontPointSize(15);
    ui->textBrowser_ChatLog->append(friendmessage->getName()+":");
    ui->textBrowser_ChatLog->append(str);
}

