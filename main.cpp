#include "CalculatorWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CalculatorWidget calculatorWidget;
    calculatorWidget.show();
    return app.exec();
}
