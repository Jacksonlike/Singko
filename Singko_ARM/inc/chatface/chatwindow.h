#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QHostAddress>
#include <QTableWidget>
#include <chattext.h>
#include "expression.h"
#include "Message.h"
#include "userMessage.h"
#include "ownMessage.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0,userMessage * fri = 0);
    void init_button();
    void display();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent * event);
    void show_friendInformation(userMessage *friendMessage);

    ~ChatWindow();
signals:
    void sig_pushbutton_send();
private slots:
    void slot_rev_file(QHostAddress addrip, QString file);
    void on_pushButton_FaceExpression_clicked();
    void slots_expression_clicked(QTableWidgetItem* Item);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void slot_button_message(QString str);
    void on_mini_pushbutton_clicked();
    void on_close_pushbutton_clicked();

    void on_pushButton_sendfile_clicked();

private:
    Ui::ChatWindow *ui;
    expression *myexpression;
    ownMessage *mymessage;
    userMessage *friendmessage;
    ChatText *textEdit_sendmessage;
    QPoint dPos;

    bool mov;
};

#endif // CHATWINDOW_H
