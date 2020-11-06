#include "CalculatorWidget.h"

CalculatorWidget::CalculatorWidget(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setupSignalSlot();
}

void CalculatorWidget::insertTextToExpressionTextBrowser(QString& text)
{
    // there's some problems to do with QTextBrower::insertPlainText
    // so we use this method
    QString& expression = ui.expressionPlainTextEdit->toPlainText();
    expression.append(text);
    ui.expressionPlainTextEdit->setPlainText(expression);
    evaluateExpression();
}

void CalculatorWidget::removeLastCharFromExpressionTextBrowser()
{
    QString& currentExpression = ui.expressionPlainTextEdit->toPlainText();
    if (currentExpression.size() > 0)
        ui.expressionPlainTextEdit->setPlainText(currentExpression.remove(currentExpression.size()-1, 1));

    if (currentExpression.size() == 0)
        ui.resultTextBrowser->clear();
    else
        evaluateExpression();
}

void CalculatorWidget::clearExpressionTextBrowser()
{
    ui.expressionPlainTextEdit->clear();
    ui.resultTextBrowser->clear();
}

void CalculatorWidget::evaluateExpression()
{
    string& expression = ui.expressionPlainTextEdit->toPlainText().toStdString();
    if (expression.length() == 0)
        ui.resultTextBrowser->clear();
    else
    {
        double result;
        if (evaluateStringExpression(expression, &result))
            ui.resultTextBrowser->setText(QString::number(result));
        else
            ui.resultTextBrowser->setText("Error");
    }
}

void CalculatorWidget::keyPressEvent(QKeyEvent* k)
{
    switch (k->key())
    {
    // we use QButton::animateClick instead of calling insertTextToExpressionTextBrowser directly
    // is because that we want to display the animation of a button click
    case Qt::Key::Key_0: ui.button0->animateClick(); break;
    case Qt::Key::Key_1: ui.button1->animateClick(); break;
    case Qt::Key::Key_2: ui.button2->animateClick(); break;
    case Qt::Key::Key_3: ui.button3->animateClick(); break;
    case Qt::Key::Key_4: ui.button4->animateClick(); break;
    case Qt::Key::Key_5: ui.button5->animateClick(); break;
    case Qt::Key::Key_6: ui.button6->animateClick(); break;
    case Qt::Key::Key_7: ui.button7->animateClick(); break;
    case Qt::Key::Key_8: ui.button8->animateClick(); break;
    case Qt::Key::Key_9: ui.button9->animateClick(); break;
    case Qt::Key::Key_Slash:       ui.divideButton->animateClick(); break;
    case Qt::Key::Key_Period:      ui.dotButton->animateClick(); break;
    case Qt::Key::Key_ParenLeft:   ui.leftParenthesisButton->animateClick(); break;
    case Qt::Key::Key_ParenRight:  ui.rightPatenthesisButton->animateClick(); break;
    case Qt::Key::Key_Minus:       ui.minusButton->animateClick(); break;
    case Qt::Key::Key_Percent:     ui.modButton->animateClick(); break;
    case Qt::Key::Key_Asterisk:    ui.multiplyButton->animateClick(); break;
    case Qt::Key::Key_Plus:        ui.plusButton->animateClick(); break;
    case Qt::Key::Key_AsciiCircum: ui.powButton->animateClick(); break;
    case Qt::Key::Key_Ampersand:   ui.rootButton->animateClick(); break;

    case Qt::Key::Key_Backspace: ui.backspaceButton->animateClick(); break;
    case Qt::Key::Key_Equal:     ui.equalButton->animateClick(); break;
    case Qt::Key::Key_C:         ui.clearButton->animateClick(); break;
    }
}

void CalculatorWidget::setupSignalSlot()
{
    // connect operator and operand buttons
    connect(ui.button0, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('0'));});
    connect(ui.button1, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('1')); });
    connect(ui.button2, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('2')); });
    connect(ui.button3, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('3')); });
    connect(ui.button4, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('4')); });
    connect(ui.button5, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('5')); });
    connect(ui.button6, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('6')); });
    connect(ui.button7, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('7')); });
    connect(ui.button8, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('8')); });
    connect(ui.button9, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString('9')); });
    connect(ui.divideButton, &QPushButton::clicked,           [=]() {this->insertTextToExpressionTextBrowser(QString('/')); });
    connect(ui.dotButton, &QPushButton::clicked,              [=]() {this->insertTextToExpressionTextBrowser(QString('.')); });
    connect(ui.leftParenthesisButton, &QPushButton::clicked,  [=]() {this->insertTextToExpressionTextBrowser(QString('(')); });
    connect(ui.rightPatenthesisButton, &QPushButton::clicked, [=]() {this->insertTextToExpressionTextBrowser(QString(')')); });
    connect(ui.minusButton, &QPushButton::clicked,            [=]() {this->insertTextToExpressionTextBrowser(QString('-')); });
    connect(ui.modButton, &QPushButton::clicked,              [=]() {this->insertTextToExpressionTextBrowser(QString('%')); });
    connect(ui.multiplyButton, &QPushButton::clicked,         [=]() {this->insertTextToExpressionTextBrowser(QString('*')); });
    connect(ui.plusButton, &QPushButton::clicked,             [=]() {this->insertTextToExpressionTextBrowser(QString('+')); });
    connect(ui.powButton, &QPushButton::clicked,              [=]() {this->insertTextToExpressionTextBrowser(QString('^')); });
    connect(ui.rootButton, &QPushButton::clicked,             [=]() {this->insertTextToExpressionTextBrowser(QString('&')); });

    connect(ui.backspaceButton, &QPushButton::clicked, this, &CalculatorWidget::removeLastCharFromExpressionTextBrowser);
    connect(ui.clearButton, &QPushButton::clicked, this,     &CalculatorWidget::clearExpressionTextBrowser);
    connect(ui.equalButton, &QPushButton::clicked, this,     &CalculatorWidget::evaluateExpression);
    connect(ui.helpButton, &QPushButton::clicked, [=]() {QDesktopServices::openUrl(QString("https://github.com/xyqyear/calculator")); });

    connect(ui.expressionPlainTextEdit, &QPlainTextEdit::textChanged, this, &CalculatorWidget::evaluateExpression);
}
