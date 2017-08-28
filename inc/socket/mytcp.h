#ifndef MYTCP_H
#define MYTCP_H
#include <QTcpSocket>
#include <QTcpServer>

#include <QObject>

class Mytcp: public QObject
{
    Q_OBJECT
public:
    Mytcp();
    void sendFile(QHostAddress ipaddr,QString filepath);
    void sendDir(QHostAddress ipaddr,QString dirname);

public slots:
    void revFile();
    void revDir();
    void onConnected();
    void onNewconnection();
signals:
    void sigRevfile(QHostAddress addrip, QString filename);
private:
    QTcpSocket * tcpsocket;
    QTcpServer * tcpserver;
};

#endif // MYTCP_H
