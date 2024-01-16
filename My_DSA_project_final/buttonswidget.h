#ifndef BUTTONSWIDGET_H
#define BUTTONSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "linefromtwopointsdialog.h"

// class MainWindow;

class ButtonsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonsWidget(QWidget *parent = nullptr);

signals:
    void arithmetic_btn_signal();
    void intersection_btn_signal();
private slots:
    void arithmetic_btn_slot();
    void intersection_btn_slot();

    void openLineFromTwoPointsDialog();
private:
    QPushButton* arithmetic_btn;
    QPushButton* straightLines_btn;

    QPushButton* intersectionOfTwoLines_btn;

    QPushButton* lineFromTwoPoints_btn;

    LineFromTwoPointsDialog* lineFromTwoPointsDialog;

    QVBoxLayout* mainLayout;
};
#endif // BUTTONSWIDGET_H
