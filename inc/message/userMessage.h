#ifndef USERMESSAGE
#define USERMESSAGE

#include <Message.h>
#include <QList>

//#include <QtDebug>
//#define DEBUG_USERMESSAGE

//==============================================================
/*                       user message
** 表示所有在线的用户信息，IP为用户之间唯一的标识，设置IP即可唯一确定用户身
** 份，定义对象后必须设置IP。
** 析构时调用WriteFile()保存信息到本地
*/
//==============================================================


class userMessage : public Message
{
public:
    userMessage(QObject *parent = 0);
    userMessage(QString IP, QObject *parent = 0);
    ~userMessage();

    inline int  getGroup();
    inline void setGroup(int num);
    inline bool isMe(QString IP);

private:
	int  groupnum;
    virtual void Readfile();
    virtual void Writefile();
};

inline void userMessage::setGroup(int num)
{
    this->groupnum = num;
}

inline int userMessage::getGroup()
{
    return this->groupnum;
}

inline bool userMessage::isMe(QString IP)
{
    if (IP == getIP())
        return true;
    return false;
}

#endif // USERMESSAGE

