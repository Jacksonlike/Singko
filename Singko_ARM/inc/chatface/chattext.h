#ifndef CHATTEXT
#define CHATTEXT
#include <QTextEdit>
#include <keyboard.h>

class ChatText : public QTextEdit
{
    Q_OBJECT

public:
    ChatText(QWidget *parent = 0);

private:
    KeyBoard *keyBoardDlg;
    QWidget *parentWidget;
    QPoint nowpos;
    void mousePressEvent(QMouseEvent *event);
    void InitkeyBoardDlg();
    void disPlayKeyBoard();

private slots:
    void displayInputContent(QString text);
    void getPos(QPoint newpos);
};







#endif // CHATTEXT

