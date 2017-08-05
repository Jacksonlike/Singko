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
    ~ownMessage();

    inline void setBackground(int back);
    inline int  getBackground();
    static QString getLocalIP();

private:
    virtual void Readfile();
    virtual void Writefile();
    int  background;
    //QStringList group;

};

inline void ownMessage::setBackground(int back)
{
    this->background = back;
}

inline int ownMessage::getBackground()
{
    return this->background;
}


#endif // OWNMESSAGE

