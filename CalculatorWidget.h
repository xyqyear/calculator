#pragma once

#include <iostream>
#include <QtWidgets/QMainWindow>
#include <qevent.h>
#include "ui_Calculator.h"
#include "calculator.h"
using namespace std;

class CalculatorWidget : public QMainWindow
{
    Q_OBJECT

public:
    CalculatorWidget(QWidget *parent = Q_NULLPTR);

public slots:
    void insertTextToExpressionTextBrowser(QString& text);
    void removeLastCharFromExpressionTextBrowser();
    void clearExpressionTextBrowser();
    void evaluateExpression();
    void keyPressEvent(QKeyEvent* k);

private:
    // properties
    Ui::CalculatorClass ui;
    bool isFirstInsertion;

    // mothods
    void setupSignalSlot();
};
