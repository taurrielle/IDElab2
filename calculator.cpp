#include "calculator.h"
#include "ui_calculator.h"


double firstNum;
bool typing = false;
bool scietificButton = false;
bool typing_2 = false;
bool bynary_pressed = false;
bool showPlot = false;
bool operationPressed = false;
bool equalPressed = false;
QString pending_operator;

Calculator::Calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    connect(ui -> pushButton_0, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_1, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_2, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_3, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_4, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_5, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_6, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_7, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_8, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui -> pushButton_9, SIGNAL(released()), this, SLOT(digitPressed()));

    connect(ui -> pushButton_sign, SIGNAL(released()), this, SLOT(unaryOperationPressed()));
    connect(ui -> pushButton_percent, SIGNAL(released()), this, SLOT(unaryOperationPressed()));
    connect(ui -> pushButton_sqrt, SIGNAL(released()), this, SLOT(unaryOperationPressed()));
    connect(ui -> pushButton_pow, SIGNAL(released()), this, SLOT(unaryOperationPressed()));
    connect(ui -> pushButton_overx, SIGNAL(released()), this, SLOT(unaryOperationPressed()));

    connect(ui -> pushButton_add, SIGNAL(released()), this, SLOT(binaryOperationPressed()));
    connect(ui -> pushButton_subtract, SIGNAL(released()), this, SLOT(binaryOperationPressed()));
    connect(ui -> pushButton_multiply, SIGNAL(released()), this, SLOT(binaryOperationPressed()));
    connect(ui -> pushButton_divide, SIGNAL(released()), this, SLOT(binaryOperationPressed()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);

    ui->pushButton_pow->setCheckable(true);
    ui->pushButton_sqrt->setCheckable(true);
    ui->pushButton_overx->setCheckable(true);
    ui->pushButton_percent->setCheckable(true);

    this->setFixedSize(279,430);

    ui->label->setFixedWidth(281);
    ui->qCustomPlot->hide();
    ui->pushButton_back->hide();

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::digitPressed()
{
    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if ((bynary_pressed) && (!typing))
    {
        labelNumber = button->text().toDouble();
        typing = true;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_3->setText(ui->label_3->text() + " " + newLabel);
    }
    else
    {
        if(ui->label->text().contains(".") && button->text() == "0")
        {
            newLabel = ui->label->text() + button->text();
        }
        else if(equalPressed == true)
        {
            labelNumber = button->text().toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label_3->setText("");
        }
        else
        {
            labelNumber = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
        }

        if(ui->label->text().contains("0") && ui->label->text().length() == 1)
        {
            ui->label_3->setText(button->text());
        }
        else
        {
            ui->label_3->setText(ui->label_3->text() + button->text());
        }

    }
    ui->label->setText(newLabel);
    operationPressed = false;
    equalPressed = false;
    showPlot = false;

}

void Calculator::on_pushButton_decimal_released()
{
    if(!(ui->label->text().contains(".")))
    {
        ui->label->setText(ui->label->text() + ".");
        ui->label_3->setText(ui->label_3->text() + ".");
    }
}

void Calculator::unaryOperationPressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;
    equalPressed = true;

    if (button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * (-1);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->label_3->setText(newLabel);
    }

    else if (button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->label_3->setText(ui->label_3->text() + "%");
    }

    else if (button->text() == "√")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = sqrt(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->label_3->setText("√" + ui->label_3->text());
    }

    else if (button->text() == "x^2")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = pow(labelNumber, 2);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->label_3->setText(ui->label_3->text() + " ^ 2");
    }

    else if (button->text() == "1/x")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = 1 / labelNumber;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->label_3->setText("1 / " + ui->label_3->text());
    }
}

void Calculator::on_pushButton_clear_released()
{
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    ui->pushButton_pow->setChecked(false);
    ui->pushButton_sqrt->setChecked(false);
    ui->pushButton_overx->setChecked(false);
    ui->pushButton_percent->setChecked(false);

    typing = false;

    bynary_pressed = false;
    showPlot = false;

    ui->label->setText("0");
    ui->label_3->setText("0");
    firstNum = 0;
}

void Calculator::on_pushButton_equal_released()
{
    double labelNumber, secondNum;
    QString newLabel;
    equalPressed = true;

    secondNum = ui->label->text().toDouble();
    if (showPlot == false)
    {
        if (ui->pushButton_add->isChecked())
        {
            labelNumber = firstNum + secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
            ui->label_3->setText(newLabel);
            ui->pushButton_add->setChecked(false);
        }
        else if (ui->pushButton_subtract->isChecked())
        {
            labelNumber = firstNum - secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
            ui->label_3->setText(newLabel);
            ui->pushButton_subtract->setChecked(false);
        }
        else if (ui->pushButton_multiply->isChecked())
        {
            labelNumber = firstNum * secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
            ui->label_3->setText(newLabel);
            ui->pushButton_multiply->setChecked(false);
        }
        else if (ui->pushButton_divide->isChecked())
        {
            labelNumber = firstNum / secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
            ui->label_3->setText(newLabel);
            ui->pushButton_divide->setChecked(false);
        }
        else if (ui->pushButton_pow->isChecked())
        {
            ui->label_3->setText(ui->label->text());
            ui->pushButton_pow->setChecked(false);
        }
        else if (ui->pushButton_sqrt->isChecked())
        {
            ui->label_3->setText(ui->label->text());
            ui->pushButton_sqrt->setChecked(false);
        }
        else if (ui->pushButton_overx->isChecked())
        {
            ui->label_3->setText(ui->label->text());
            ui->pushButton_overx->setChecked(false);
        }
        else if (ui->pushButton_percent->isChecked())
        {
            ui->label_3->setText(ui->label->text());
            ui->pushButton_percent->setChecked(false);
        }
    }

    else if(showPlot == true)
    {
        ui->qCustomPlot->show();
        ui->pushButton_back->show();
        QString expr, exprTemp;
        QVector<double> x(21), y(21);
        expr = ui->label_3->text();

        for(int i=0; i<21;i++)
        {
            exprTemp = expr;

            int j = i - 10;
            QString tempX = QString::number(j);;
            exprTemp = exprTemp.replace("x", tempX);
            QScriptEngine expression;
            double myVal=expression.evaluate(exprTemp).toNumber();
            x[i] = j;
            y[i] = myVal;
        }
        // create graph and assign data to it:
        ui->qCustomPlot->addGraph();
        ui->qCustomPlot->graph(0)->setData(x, y);

        // set axes ranges, so we see all data:
        ui->qCustomPlot->xAxis->setRange(-10, 10);
        ui->qCustomPlot->yAxis->setRange(-10, 10);
        ui->qCustomPlot->replot();
        showPlot = false;
    }

    typing = false;
    firstNum = 0;
    bynary_pressed = false;
}

void Calculator::binaryOperationPressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber, secondNum;
    QString newLabel;

    equalPressed = false;
    if(operationPressed == true)
    {
        ui->pushButton_add->setChecked(false);
        ui->pushButton_subtract->setChecked(false);
        ui->pushButton_multiply->setChecked(false);
        ui->pushButton_divide->setChecked(false);

        ui->pushButton_pow->setChecked(false);
        ui->pushButton_sqrt->setChecked(false);
        ui->pushButton_overx->setChecked(false);
        ui->pushButton_percent->setChecked(false);
        bynary_pressed = false;
        typing = false;
        ui->label_3->setText(ui->label_3->text().left((ui->label_3->text().length() - 2)));
    }

    button->setChecked(true);
    ui->label_3->setText(ui->label_3->text() + " " + button->text());

    if (bynary_pressed == false)
    {
        firstNum = ui->label->text().toDouble();

        bynary_pressed = true;
        pending_operator = button->text();
    }

    else if (ui->pushButton_add->isChecked() && bynary_pressed && (pending_operator == "+"))
    {
        secondNum = ui->label->text().toDouble();
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        firstNum = ui->label->text().toDouble();
        pending_operator = button->text();
    }
    else if (ui->pushButton_subtract->isChecked() && bynary_pressed && (pending_operator == "-"))
    {
        secondNum = ui->label->text().toDouble();
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        firstNum = ui->label->text().toDouble();
        pending_operator = button->text();
    }
    else if (ui->pushButton_multiply->isChecked() && bynary_pressed && (pending_operator == "x"))
    {
        secondNum = ui->label->text().toDouble();
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        firstNum = ui->label->text().toDouble();
        pending_operator = button->text();
    }
    else if (ui->pushButton_divide->isChecked() && bynary_pressed && (pending_operator == "/"))
    {
        secondNum = ui->label->text().toDouble();
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        firstNum = ui->label->text().toDouble();
        pending_operator = button->text();
    }
    else if ((ui->pushButton_add->isChecked() && bynary_pressed && (pending_operator != "+")) ||
             (ui->pushButton_subtract->isChecked() && bynary_pressed && (pending_operator != "-")) ||
             (ui->pushButton_multiply->isChecked() && bynary_pressed && (pending_operator != "x")) ||
             (ui->pushButton_divide->isChecked() && bynary_pressed && (pending_operator != "/")))
    {
        if (pending_operator == "+")
        {
            secondNum = ui->label->text().toDouble();
            labelNumber = firstNum + secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
            firstNum = ui->label->text().toDouble();

        }
        else if (pending_operator == "-")
        {
            secondNum = ui->label->text().toDouble();
            labelNumber = firstNum - secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
            firstNum = ui->label->text().toDouble();
        }
        else if (pending_operator == "x")
        {
            secondNum = ui->label->text().toDouble();
            labelNumber = firstNum * secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
            firstNum = ui->label->text().toDouble();
        }
        else if (pending_operator == "/")
        {
            secondNum = ui->label->text().toDouble();
            labelNumber = firstNum / secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
            firstNum = ui->label->text().toDouble();
        }
        pending_operator = button->text();
    }
    typing = false;
    operationPressed = true;
}

void Calculator::on_pushButton_del_released()
{
    QString textLabel, textLabel_3;
    typing = false;

    textLabel = ui->label->text();
    textLabel_3 = ui->label_3->text();
    if (textLabel.size() == 1)
    {
        ui->label->setText("0");
        ui->label_3->setText(textLabel_3.left((textLabel_3.length() - 1)));
    }
    else
    {
        ui->label->setText(textLabel.left((textLabel.length() - 1)));
        ui->label_3->setText(textLabel_3.left((textLabel_3.length() - 1)));
    }
}

void Calculator::on_pushButton_change_2_released()
{
    if(scietificButton == false)
    {
        this->setFixedSize(350,430);
        ui->label->setFixedWidth(350);
        ui->label_2->setText("Scientific");
        ui->label_2->setFixedWidth(300);
        ui->label_3->setFixedWidth(350);
        ui->pushButton_equal->setFixedWidth(142);
        scietificButton = true;
    }
    else if (scietificButton == true)
    {
        this->setFixedSize(279,430);
        ui->label->setFixedWidth(280);
        ui->label_2->setText("Standard");
        ui->label_2->setFixedWidth(230);
        ui->label_3->setFixedWidth(280);
        ui->pushButton_equal->setFixedWidth(71);
        scietificButton = false;
    }
}

void Calculator::on_pushButton_function_released()
{
    showPlot = true;

    if(bynary_pressed == true && typing == false)
    {
        ui->label->setText(" x");
        ui->label_3->setText(ui->label_3->text() + " x");
    }
    else if(ui->label->text()[0] == "0")
    {
        ui->label->setText("x");
        ui->label_3->setText("x");
    }
    else if(ui->label->text()[ui->label->text().length() -1] == "x")
    {
        ui->label->setText("x");
        ui->label_3->setText(ui->label_3->text() + " * x");
    }
    else
    {
        ui->label->setText(ui->label->text() + "x");
        ui->label_3->setText(ui->label_3->text() + " * x");
    }
}

void Calculator::on_pushButton_back_released()
{
    if(showPlot == false)
        {
            ui->qCustomPlot->hide();
            ui->pushButton_back->hide();
        }
    showPlot = true;
}
