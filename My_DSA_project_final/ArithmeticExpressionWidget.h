#ifndef ARITHMETICEXPRESSIONWIDGET_H
#define ARITHMETICEXPRESSIONWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <vector>

class ArithmeticExpressionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ArithmeticExpressionWidget(QWidget *parent = nullptr);

signals:

    void goBackClicked();

private:
    QTextEdit *inputTextEdit;
    QPushButton *solveButton;
    QLabel *resultLabel;
    QTextEdit* resultTextEdit;
    QPushButton *goBackButton;
    std::string infixToPostfix(QString& infix);

    std::string plus(std::string& a, std::string& b);
    std::string subtract(std::string& a, std::string& b, bool isDivision = false);
    std::string multiply(std::string& a, std::string& b);
    std::string divide(std::string& a, std::string& b);
    std::string power(std::string &x , std::string& n);
    void removeTrailingZeroes(std::string &s);
    long long findDecimalIndexAndRemove(std::string &s);

    std::string evaluatePostfix(std::string& postfix);


private slots:
    void solveArithmeticExpression();
    void goBack();
};

#endif // ARITHMETICEXPRESSIONWIDGET_H
