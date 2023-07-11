#include <QtWidgets>
#include <QLabel>
#include <QApplication>
#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //
    Calculator calculator;
    calculator.setWindowTitle("Calculator");
    calculator.resize(345, 530);
    calculator.show();
    //
    return a.exec();
}
