#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QToolBox>
#include <userMessage.h>
#include <friendpushbutton.h>
#include <groupwidget.h>

#include <QtDebug>
#define  DEBUG_TOOLBOX

//==============================================================
/*                        Toolbox
** 好友列表，1)管理在线的用户 2)管理分组信息
** 好友下线会在列表中将其删除，好友上线则增加好友按钮
** 管理用户分组信息，提供增加用户分组和删除用户分组的功能
** =============================================================
** 有两个重要数据成员：
** 1）usrtable
**    在线用户列表，使用QMap进行管理，key值为32位的IP地址，value
** 值为该IP所对应用户的按钮图标。
** 2）friendlist
**     管理分组，使用QMap进行管理，key值为组编号，value值为组
** 界面。
** =============================================================
** 两个重要的函数成员：
** 1）void addContacts(userMessage *someone);
** A、判断是否已上线。
** B、若没有上线，则创建FriendPushbutton,加入对应信息到usrtable。
** C、确定分组情况，将好友加入分组中的末尾。
** 2）void deleteContacts(QString IP);
** A、判断要下线的联系人是否在在线好友列表中
** B、若在好友列表中，则析构FriendPushbutton，删除usrtable对应信息。
** C、刷新GroupWidget列表，顺序重新排列
*/
//==============================================================

class Toolbox : public QToolBox
{
    Q_OBJECT
public:
    explicit Toolbox(QWidget *parent = 0);
    ~Toolbox();

signals:

public slots:
    void addContacts(userMessage *someone);
    void deleteContacts(QString IP);
    void slot_currentChanged(int index);
//    void setGroups(int num, QString title);
//    void addGroups(QString title);
//    void deleteGroup(int num);

private:
    void Readfile();
    void Writefile();
    int index_old;
    QMap<int, GroupWidget *> friendlist;                  //用户分组信息管理
    QMap<quint32, FriendPushbutton *> usrtable;
};

#endif // TOOLBOX_H
