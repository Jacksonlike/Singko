#include <chattext.h>
#include <QDebug>
#include <QMouseEvent>


ChatText::ChatText(QWidget *parent)
    :QTextEdit(parent),nowpos(300, 50)
{
    InitkeyBoardDlg();
    //parentWidget = parent;
}

void ChatText::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mousePressEvent";
    if( event->type()== QEvent::MouseButtonPress )
    {
        qDebug()<<"LeftButton";
        disPlayKeyBoard();
    }
}
void ChatText::InitkeyBoardDlg()
{
    keyBoardDlg = new KeyBoard();
    keyBoardDlg->setWindowFlags(Qt::Tool|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    connect(keyBoardDlg,SIGNAL(setvalue(QString)),this,SLOT(displayInputContent(QString)));
    connect(keyBoardDlg,SIGNAL(setnewpos(QPoint)),this,SLOT(getPos(QPoint)));
}

void ChatText::disPlayKeyBoard()
{
    keyBoardDlg->move(nowpos);
    keyBoardDlg->show();
}

void ChatText::displayInputContent(QString text)
{
    qDebug()<<"TextEdit::displayInputContent";
    append(text);
//    setText(text);
}

void ChatText::getPos(QPoint newpos)
{
    nowpos = newpos;
}
