#include <QDebug>
#include <QDir>
#include <QTextDocumentFragment>
#include <QColor>
#include <QFileDialog>
#include <QBitmap>
#include "ui_chatwindow.h"
#include "mytcp.h"
#include "expression.h"
#include "chatwindow.h"
#include "mysocket.h"
#include "widget.h"

extern Mysocket *myudpSocket;
extern Mytcp *mytcpSocket;
ChatWindow::ChatWindow(QWidget *parent, userMessage * fri):
    QDialog(parent),
    ui(new Ui::ChatWindow), friendmessage(fri),
    mymessage(new ownMessage), myexpression(new expression(this))
{
    ui->setupUi(this);

    display();

    connect(mytcpSocket, SIGNAL(sigRevfile(QHostAddress,QString)),
            this,SLOT(slotRevFile(QHostAddress,QString)));
}


void ChatWindow::initButton()
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

}


void ChatWindow::showFriendinformation(userMessage* friendMessage)
{
   ui->textBrowser_friendInformation->append("Username: "+friendMessage->getName());
   ui->textBrowser_friendInformation->append("Hostname: "+friendMessage->getHostname());
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
    emit chatWindowclosed();
    delete myexpression;
    delete mymessage;
    delete ui;
}

void ChatWindow::on_pushButton_FaceExpression_clicked()
{
    myexpression->show();
   // myexpression->exec();
}

void ChatWindow::slotsExpressionClicked(QTableWidgetItem* Item)
{

    int num = Item->row()*8 + Item->column();
    QDir *expression_dir = new QDir(":/face/face/");
    QStringList myexpression_list = expression_dir->entryList();//文件名列表
    QList<QString>::iterator i = myexpression_list.begin();
    i+=num;
    QString filename(":/face/face/"+*i);
    QTextImageFormat imageFormat;   //保存图片格式对象
    imageFormat.setName(filename);
    imageFormat.setHeight(40);
    imageFormat.setWidth(40);

    //获取当前光标
    QTextCursor cursor = ui->textEdit_sendmessage->textCursor();
    cursor.insertImage(imageFormat);

    myexpression->close();
    delete expression_dir;
}

void ChatWindow::on_pushButton_2_clicked()//发送聊天消息，并更新自己界面
{
    QFont font ( "Microsoft YaHei", 10, 75);
    ui->textBrowser_ChatLog->setFont(font);

    QString text = ui->textEdit_sendmessage->toHtml();
    qDebug() << text;
    if (text.isEmpty())
        return;
    ui->textBrowser_ChatLog->append(mymessage->getName()+":");
    ui->textBrowser_ChatLog->append(text);
    myudpSocket->sendMessage(QHostAddress(friendmessage->getIP()),
                              ui->textEdit_sendmessage->toHtml());
    ui->textEdit_sendmessage->clear();
}

void ChatWindow::on_pushButton_clicked()
{
    delete this;
}

void ChatWindow::slotButtonMessage(QString str)
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
    initButton();
    showFriendinformation(friendmessage);

    setWindowIcon(QIcon(":/other/image/logo.ico"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("border-radius: 5px");

    QPalette pal;
    QPixmap pic = QPixmap(QString(":/other/image/chatbackground.png"));

    pic.setMask(QBitmap(QPixmap(QString(":/other/image/chatbackgroundmask.png"))));
    pal.setBrush(QPalette::Background, QBrush(pic));
    setPalette(pal);
}



void ChatWindow::on_pushButton_sendfile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this);
    qDebug()<<"file : "<<file;
    mytcpSocket->sendFile(QHostAddress(friendmessage->getIP()), file);
    ui->textBrowser_ChatLog->append("send succeed :"+file);
}

void ChatWindow::slotRevFile(QHostAddress addrip, QString file)
{
    qDebug()<<"slotRevFile";
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
