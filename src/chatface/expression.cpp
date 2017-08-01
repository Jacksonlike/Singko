#include "expression.h"
#include "ui_expression.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <chatwindow.h>


expression::expression(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::expression)
{
    ui->setupUi(this);
    init_expression();
    connect(ui->tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)),
           parent,SLOT(slots_expression_clicked(QTableWidgetItem*)));
}

void expression::init_expression()
{
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(8);

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(40);//设置每格宽度
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40);//设置每格高度

    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setIconSize(QSize(30,30));
    QDir *expression_dir = new QDir(":/face");
    QStringList myexpression = expression_dir->entryList();//文件名列表
    QList<QString>::iterator i;

    QIcon new_icon;
    int row = 0;
    int column =0;
    for(i = myexpression.begin(); i != myexpression.end();i++)
    {
        new_icon = QIcon(QString(":/face/")+*i);
        qDebug()<<QString(":/face")+*i;
        QTableWidgetItem *new_item = new QTableWidgetItem(new_icon,"");

        ui->tableWidget->setItem(row,column,new_item);
        if(column == 7)
        {
            row++;
            column=1;
        }
       column++;
    }
}

expression::~expression()
{
    delete ui;
}
