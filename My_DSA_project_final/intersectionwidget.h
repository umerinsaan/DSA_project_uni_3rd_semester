#ifndef INTERSECTIONWIDGET_H
#define INTERSECTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>

class IntersectionWidget : public QWidget
{
    Q_OBJECT

public:
    IntersectionWidget(QWidget *parent = nullptr);

signals:
    void goBackClicked();

private slots:
    void findIntersection();
    void onGoBackClicked();

private:
    QLabel *equationLabel;
    QLabel *equation2Label;
    QLineEdit *equationLineEdit;
    QLineEdit *equation2LineEdit;
    QPushButton *findIntersectionButton;
    QLabel *xCoordinateLabel;
    QLabel *yCoordinateLabel;
    QPushButton *goBackButton;

    void setupUI();
};

#endif // INTERSECTIONWIDGET_H
