#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QToolBox>
#include <userMessage.h>

#include <QtDebug>
#define  DEBUG_TOOLBOX

//==============================================================
/*                        Toolbox
** 好友列表，管理在线的用户，好友下线会在列表中将其删除
** 管理用户分组信息，提供增加用户分组和删除用户分组的功能
*/
//==============================================================

typedef struct
{
    userMessage * user;
}va;


class Toolbox : public QToolBox
{
    Q_OBJECT
public:
    explicit Toolbox(QWidget *parent = 0);



signals:

public slots:
    void addContacts(userMessage *someone);
    void deleteContacts(userMessage *someone);

private:
    void Readfile();
    void Writefile();
    QList <userMessage *> OnlineContects;
    QMap<int, QString> friendlist;
};

#endif // TOOLBOX_H
