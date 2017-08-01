#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QHostAddress>
#include "expression.h"
#include <QTableWidget>
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
    explicit ChatWindow(QDialog *parent = 0,userMessage * fri = 0);
    void init_button();

    void show_friendInformation(userMessage *friendMessage);

    ~ChatWindow();
signals:
    void sig_pushbutton_send();
private slots:
    void on_pushButton_FaceExpression_clicked();
    void slots_expression_clicked(QTableWidgetItem* Item);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void slot_button_message(QString str);

private:
    Ui::ChatWindow *ui;
    expression *myexpression;
    ownMessage *mymessage;
    userMessage *friendmessage;
};

#endif // CHATWINDOW_H
