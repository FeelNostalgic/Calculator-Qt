#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>

#include <QDebug>

#define PI 3.14159265

double firstNum;
bool bUserIsTypingSecondNumber;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->UnaryButton,SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->PercentButton,SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui->AddButton,SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->DivideButton,SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->SubstractButton,SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->MultiplyButton,SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->PowButton,SIGNAL(released()), this, SLOT(binary_operation_pressed()));

    connect(ui->CosButton,SIGNAL(released()), this, SLOT(trigonometric_operaction_pressed()));
    connect(ui->SinButton,SIGNAL(released()), this, SLOT(trigonometric_operaction_pressed()));
    connect(ui->TanButton,SIGNAL(released()), this, SLOT(trigonometric_operaction_pressed()));

    ui->AddButton->setCheckable(true);
    ui->DivideButton->setCheckable(true);
    ui->SubstractButton->setCheckable(true);
    ui->MultiplyButton->setCheckable(true);
    ui->PowButton->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetLabelText(double number)
{
    QString newLabel = QString::number(number, 'g', 15);

    ui->label->setText(newLabel);
}

void MainWindow::digit_pressed()
{
    //qDebug() << "test";
    QPushButton * button = (QPushButton*) sender();

    double labelNumber;
    QString newLabel;

    if ((ui->AddButton->isChecked() || ui->SubstractButton->isChecked() || ui->MultiplyButton->isChecked() || ui->DivideButton->isChecked() || ui->PowButton->isChecked() ) && (!bUserIsTypingSecondNumber))
    {
        labelNumber = (button->text()).toDouble();
        bUserIsTypingSecondNumber = true;
        newLabel = QString::number(labelNumber,'g',15);

    }else
    {
        if(ui->label->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->label->text() + button->text();
        }else
        {
            labelNumber = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber,'g',15);
        }
    }

    ui->label->setText(newLabel);
}

void MainWindow::on_DecimalButton_released()
{
    if(ui->label->text().contains('.')) return;

    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;

    if(button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;

        SetLabelText(labelNumber);
    }

    if(button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;

        SetLabelText(labelNumber);
    }
}

void MainWindow::on_ClearButton_released()
{
    SetLabelText(0);
    ui->AddButton->setChecked(false);
    ui->SubstractButton->setChecked(false);
    ui->MultiplyButton->setChecked(false);
    ui->DivideButton->setChecked(false);
    ui->PowButton->setChecked(false);

    bUserIsTypingSecondNumber = false;
}

void MainWindow::on_EqualsButton_released()
{
    double labelNumber = 0;
    double secondNum;

    secondNum = ui->label->text().toDouble();

    if(ui->AddButton->isChecked())
    {
        labelNumber = firstNum + secondNum;
        ui->AddButton->setChecked(false);
    }
    else if(ui->SubstractButton->isChecked())
    {
        labelNumber = firstNum - secondNum;
        ui->SubstractButton->setChecked(false);
    }
    else if(ui->MultiplyButton->isChecked())
    {
        labelNumber = firstNum * secondNum;
        ui->MultiplyButton->setChecked(false);
    }
    else if(ui->DivideButton->isChecked())
    {
        labelNumber = firstNum / secondNum;
        ui->DivideButton->setChecked(false);
    }else if(ui->PowButton->isChecked())
    {
        labelNumber = pow(firstNum, secondNum);
        ui->PowButton->setChecked(true);
    }

    bUserIsTypingSecondNumber = false;
    SetLabelText(labelNumber);
}

void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);
}


void MainWindow::on_SqrtButton_released()
{
    double labelNumber = ui->label->text().toDouble();

    double result = sqrt(labelNumber);

    SetLabelText(result);

}

void MainWindow::trigonometric_operaction_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    QString buttonLabel = button->text();
    double labelNumber = ui->label->text().toDouble();
    double result = 0;

    if(buttonLabel == "cos")
    {
        result = cos(labelNumber*PI / 180);
    }else if(buttonLabel == "sin")
    {
        result = sin(labelNumber*PI / 180);
    }else if(buttonLabel == "tan")
    {
        result = tan(labelNumber*PI / 180);
    }

    SetLabelText(result);

}

