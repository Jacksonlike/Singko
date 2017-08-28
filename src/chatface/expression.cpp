#include "expression.h"
#include "ui_expression.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include "chatwindow.h"


expression::expression(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::expression)
{
    ui->setupUi(this);
    initExpression();
    connect(ui->tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)),
           parent,SLOT(slots_expression_clicked(QTableWidgetItem*)));
//    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowTitle("Emoji");
}

void expression::initExpression()
{
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(8);

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(40);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40;

    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setIconSize(QSize(30,30));

    QDir *expressionDir = new QDir(":/face/face");
    QStringList myexpression = expressionDir->entryList();//文件名列表
    QList<QString>::iterator i;

    QIcon newIcon;
    int row = 0;
    int column =0;
    for(i = myexpression.begin(); i != myexpression.end(); i++)
    {
        newIcon = QIcon(QString(":/face/face/")+*i);
        QTableWidgetItem *new_item = new QTableWidgetItem(newIcon,"");

        ui->tableWidget->setItem(row,column,new_item);
        if(column == 9)
        {
            row++;
            column=1;
        }
       column++;
    }
    delete expressionDir;
}

expression::~expression()
{
    delete ui;
}
