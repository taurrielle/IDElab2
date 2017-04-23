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

}

void Calculator::on_pushButton_decimal_released()
{
    if(!(ui->label->text().contains(".")))
    {
        ui->label->setText(ui->label->text() + ".");
        ui->label_3->setText(ui->label_3->text() + ".");
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

    bynary_pressed = false;

    ui->label->setText("0");
    ui->label_3->setText("0");
    firstNum = 0;
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



