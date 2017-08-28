#include "ui_chatwindow.h"
#include "expression.h"
#include "chatwindow.h"
#include "mysocket.h"
#include "widget.h"
#include <QDebug>
#include <QDir>
#include <QTextDocumentFragment>
#include <QColor>
#include <QFileDialog>
#include <mytcp.h>

extern Mysocket* myudp_socket;
extern Mytcp *mytcp_socket;
ChatWindow::ChatWindow(QWidget *parent, userMessage * fri):
    QDialog(parent),
    ui(new Ui::ChatWindow),friendmessage(fri)
{
    ui->setupUi(this);
    init_button();
    mymessage = new ownMessage;
    myexpression = new expression(this);
    textEdit_sendmessage = new ChatText(this);

    show_friendInformation(friendmessage);
    connect(mytcp_socket, SIGNAL(sigRevfile(QHostAddress,QString)),
            this,SLOT(slot_rev_file(QHostAddress,QString)));
    display();
}


void ChatWindow::init_button()
{

    ui->pushButton_picture->setIcon(QIcon(":/other/image/picture.ico"));
    ui->pushButton_picture->setIconSize(QSize(20,20));

    ui->pushButton_FaceExpression->setIcon(QIcon(":/other/image/FaceExpression.ico"));
    ui->pushButton_FaceExpression->setIconSize(QSize(20,20));

    ui->pushButton_font->setIcon(QIcon(":/other/image/font.ico"));
    ui->pushButton_font->setIconSize(QSize(20,20));
}


void ChatWindow::show_friendInformation(userMessage* friendMessage)
{

   ui->label_username->setText(friendMessage->getName());
   QString headimagename =QString(":/head/head/default_head%1.jpg")
           .arg(friendMessage->getHeadprotrait());
   ui->pushButton_headimage->setIcon(QIcon(headimagename));
   ui->pushButton_headimage->setIconSize(QSize(35,35));

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
    QTextCursor cursor = textEdit_sendmessage->textCursor();
    cursor.insertImage(imageFormat);

    myexpression->close();
    delete expression_dir;
}

void ChatWindow::on_pushButton_2_clicked()//发送聊天消息，并更新自己界面
{

    QFont font ( "Microsoft YaHei", 10, 75);
    ui->textBrowser_ChatLog->setFont(font);
    QString text = textEdit_sendmessage->toHtml();
    qDebug() << text;
    if (text.isEmpty())
        return;
    ui->textBrowser_ChatLog->append(mymessage->getName()+":");
    ui->textBrowser_ChatLog->append(text);
    myudp_socket->sendMessage(QHostAddress(friendmessage->getIP()),
                                textEdit_sendmessage->toHtml());
    textEdit_sendmessage->clear();
}

void ChatWindow::on_pushButton_clicked()
{
    delete this;
}

void ChatWindow::slot_button_message(QString str)
{
    QFont font ( "Microsoft YaHei", 10, 75);
    ui->textBrowser_ChatLog->setFont(font);
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
    textEdit_sendmessage->setGeometry(10, 345, 480, 100);
    this->setGeometry(300,0,500,480);
    setWindowIcon(QIcon(":/other/image/logo.ico"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("border-radius: 5px;");

    ui->pushButton_sendfile->setStyleSheet("QPushButton{background-color:#FFFFFF}\
                                              QPushButton:hover{background-color:#a5face;}");
    ui->pushButton_sendir->setStyleSheet("QPushButton{background-color:#FFFFFF}\
                                            QPushButton:hover{background-color:#a5face;}");
    ui->pushButton_cal->setStyleSheet("QPushButton{background-color:#FFFFFF}\
                                          QPushButton:hover{background-color:#a5face;}");
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:#FFFFFF}\
                                    QPushButton:hover{background-color:#a5face;}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:#FFFFFF}\
                                     QPushButton:hover{background-color:#a5face;}");
    ui->pushButton_font->setStyleSheet("QPushButton{background-color:transparent}\
                                    QPushButton:hover{background-color:#a5face;}");
    ui->pushButton_picture->setStyleSheet("QPushButton{background-color:transparent}\
                                   QPushButton:hover{background-color:#a5face;}");
    ui->pushButton_FaceExpression->setStyleSheet("QPushButton{background-color:transparent}\
                                       QPushButton:hover{background-color:#a5face;}");


    //按钮格式设置
    ui->close_pushbutton->setStyleSheet("QPushButton{background-color:transparent}"
                                      "QPushButton:hover{background:qlineargradient"
                                      "(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                                      "stop:0 rgba(250,0,0,150),"
                                      "stop:1 rgba(0,0,0,0));}");
    this->setWindowTitle(friendmessage->getName());
}



void ChatWindow::on_pushButton_sendfile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this);
    qDebug()<<"file : "<<file;
    mytcp_socket->sendFile(QHostAddress(friendmessage->getIP()), file);
    ui->textBrowser_ChatLog->append("send succeed :"+file);
}

void ChatWindow::slot_rev_file(QHostAddress addrip, QString file)
{
    qDebug()<<"slot_rev_file";
    if(addrip.toString() != friendmessage->getIP())
        return;
    QString filename = file.section('^',0, 0);
    QString filetext = file.section('^',1 ,1);
    ui->textBrowser_ChatLog->append("rev file :"+filename);
    filename =  QFileDialog::getSaveFileName(this, tr("Save File"),
               filename);
    QFile saveFile(filename);
    saveFile.open(QIODevice::WriteOnly);
    QTextStream out(&saveFile);
    out<<filetext;
}
