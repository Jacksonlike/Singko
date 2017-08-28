#ifndef GROUPWIDGET
#define GROUPWIDGET

#include <QWidget>
#include <friendpushbutton.h>

class GroupWidget
{
public:
    QList<FriendPushbutton *> Buttonlist;
    GroupWidget(QWidget * parent = 0, Qt::WindowFlags f = 0)
        :wid(new QWidget(parent, f)), qcount(0){}
    virtual ~GroupWidget() { delete wid; }

    inline QString getTitle();
    inline void setTitle(QString t);
    inline QWidget *getWidget();
    inline int  count();
    inline void countplus();
    inline void countreduce();

private:
    QWidget *wid;
    int qcount;
    QString title;
};

inline QString GroupWidget::getTitle()
{
    return title;
}

inline void GroupWidget::setTitle(QString t)
{
    title = t;
}

inline QWidget *GroupWidget::getWidget()
{
    return wid;
}

inline int GroupWidget::count()
{
    return qcount;
}

inline void GroupWidget::countplus()
{
    qcount++;
}

inline void GroupWidget::countreduce()
{
    qcount = qcount > 0 ? (qcount-1) : 0;
}



#endif // GROUPWIDGET
