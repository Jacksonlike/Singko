#include <widget.h>
#include <QApplication>
#include <mytcp.h>

Mysocket *myudp_socket;
Mytcp *mytcp_socket;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myudp_socket = new Mysocket;
    mytcp_socket = new Mytcp;
    Widget w;
    w.show();

    return a.exec();
}
