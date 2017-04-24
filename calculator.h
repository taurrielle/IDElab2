#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QScriptEngine>

#include <math.h>

namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void digitPressed();
    void on_pushButton_decimal_released();
    void unaryOperationPressed();
    void on_pushButton_clear_released();
    void on_pushButton_equal_released();
    void binaryOperationPressed();
    void on_pushButton_del_released();
    void on_pushButton_change_2_released();
    void on_pushButton_function_released();
    void on_pushButton_back_released();
};

#endif // CALCULATOR_H
