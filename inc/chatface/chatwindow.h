#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QHostAddress>
#include "expression.h"
#include <QTableWidget>
#include "Message.h"
#include "userMessage.h"
#include "ownMessage.h"

//==============================================================
/*                        ChatWindow
** 聊天窗口界面
** 聊天对象的信息存储于friendmessage中，由FriendPushbutton传入对象指针
*/
//==============================================================


namespace Ui {
class ChatWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0,userMessage * fri = 0);
    void initButton();
    void display();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent * event);
    void showFriendinformation(userMessage *friendMessage);
    ~ChatWindow();

signals:
    void sig_pushbutton_send();
    void chatWindowclosed();

private slots:
    void slotRevFile(QHostAddress addrip, QString file);
    void slotsExpressionClicked(QTableWidgetItem* Item);
    void slotButtonMessage(QString str);

    void on_pushButton_FaceExpression_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_mini_pushbutton_clicked();
    void on_close_pushbutton_clicked();
    void on_pushButton_sendfile_clicked();

private:
    Ui::ChatWindow *ui;
    expression *myexpression;
    ownMessage *mymessage;
    userMessage *friendmessage;
    QPoint dPos;
    bool mov;
};

#endif // CHATWINDOW_H
