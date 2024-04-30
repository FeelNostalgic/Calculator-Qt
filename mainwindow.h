#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_pressed();
    void on_DecimalButton_released();
    void unary_operation_pressed();
    void on_ClearButton_released();
    void on_EqualsButton_released();
    void binary_operation_pressed();
    void trigonometric_operaction_pressed();

    void on_SqrtButton_released();

private:
    void SetLabelText(double number);
};


#endif // MAINWINDOW_H
