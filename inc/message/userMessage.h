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

    void setGroup(int num);
    int  getGroup();
    bool isMe(QString IP);
    virtual void Readfile();
    virtual void Writefile();

private:
	int  groupnum;

};



#endif // USERMESSAGE

