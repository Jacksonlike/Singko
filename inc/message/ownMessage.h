#ifndef OWNMESSAGE
#define OWNMESSAGE

#include <Message.h>

//#include <QtDebug>
//#define DEBUG_OWNMESSAGE

//==============================================================
/*                       own message
** 表示用户的本地信息，创建对象之后自动初始化，整个程序应该只存在一个
** ownMessage对象。
*/
//==============================================================


class ownMessage : public Message
{
public:
    ownMessage(QObject *parent = 0);

    void setBackground(int back);
    int  getBackground();
    virtual void Readfile();
    virtual void Writefile();

    static QString getLocalIP();

private:
    int  background;
    //QStringList group;

};




#endif // OWNMESSAGE

