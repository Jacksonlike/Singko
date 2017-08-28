#include <widget.h>
#include <QApplication>
#include <mytcp.h>

Mysocket *myudpSocket;
Mytcp *mytcpSocket;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myudpSocket = new Mysocket;
    mytcpSocket = new Mytcp;
    Widget w;
    w.show();

    return a.exec();
}
