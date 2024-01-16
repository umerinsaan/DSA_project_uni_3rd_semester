#ifndef LINEFROMTWOPOINTSDIALOG_H
#define LINEFROMTWOPOINTSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class LineFromTwoPointsDialog : public QDialog
{
    Q_OBJECT

public:
    LineFromTwoPointsDialog(QWidget *parent = nullptr);

private slots:
    void findEquation();
    void closeDialog();

private:
    QLineEdit *x1LineEdit;
    QLineEdit *y1LineEdit;
    QLineEdit *x2LineEdit;
    QLineEdit *y2LineEdit;
    QLabel *equationLabel;
    QPushButton *findEquationButton;
    QPushButton *closeButton;

    void setupUI();
};

#endif // LINEFROMTWOPOINTSDIALOG_H
