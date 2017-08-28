#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QDialog>

namespace Ui {
class expression;
}

class expression : public QDialog
{
    Q_OBJECT

public:
    explicit expression(QDialog *parent = 0);
    void init_expression();
    ~expression();

private:
    Ui::expression *ui;
};

#endif // EXPRESSION_H
