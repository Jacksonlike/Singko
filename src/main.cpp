#include <widget.h>
#include <QApplication>

Mysocket *myudp_socket;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myudp_socket = new Mysocket;
    Widget w;
    w.show();

    return a.exec();
}
