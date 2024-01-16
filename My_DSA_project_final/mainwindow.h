#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>


#include "buttonswidget.h"
#include "ArithmeticExpressionWidget.h"
#include "intersectionwidget.h"

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

public slots:
    void arithmetic_btn_handler();
    void resetStackedWidget();

private slots:
    void goToIntersectionPage();
private:
    Ui::MainWindow *ui;

    QPushButton* solveArithmeticExpression_btn;
    QPushButton* workOnStraightLines_btn;
    QPushButton* workOnParabola_btn;
    QPushButton* workOnEllipse_btn;
    QPushButton* workOnHyperBola_btn;

    QWidget* centralWidget;
    QVBoxLayout* mainLayout;

    QStackedWidget* stackedWidget;

    ButtonsWidget* buttonsWidget;

    ArithmeticExpressionWidget* arithmeticWidget;

    IntersectionWidget* intersectionWidget;

    void connectAll();
};
#endif // MAINWINDOW_H
