#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QToolBox>
#include <userMessage.h>
#include <friend_pushbutton.h>
#include <groupwidget.h>

#include <QtDebug>
#define  DEBUG_TOOLBOX

//==============================================================
/*                        Toolbox
** 好友列表，1)管理在线的用户 2)管理分组信息
** 好友下线会在列表中将其删除，好友上线则增加好友按钮
** 管理用户分组信息，提供增加用户分组和删除用户分组的功能
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
