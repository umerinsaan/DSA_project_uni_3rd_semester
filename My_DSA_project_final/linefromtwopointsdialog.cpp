#include "linefromtwopointsdialog.h"

LineFromTwoPointsDialog::LineFromTwoPointsDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
}

void LineFromTwoPointsDialog::setupUI()
{
    x1LineEdit = new QLineEdit(this);
    y1LineEdit = new QLineEdit(this);
    x2LineEdit = new QLineEdit(this);
    y2LineEdit = new QLineEdit(this);
    equationLabel = new QLabel("Equation: ", this);
    findEquationButton = new QPushButton("Find Equation", this);
    closeButton = new QPushButton("Close", this);

    connect(findEquationButton, &QPushButton::clicked, this, &LineFromTwoPointsDialog::findEquation);
    connect(closeButton, &QPushButton::clicked, this, &LineFromTwoPointsDialog::closeDialog);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Enter the coordinates for two points:", this));
    layout->addWidget(new QLabel("Point 1 (x1, y1):", this));
    layout->addWidget(x1LineEdit);
    layout->addWidget(y1LineEdit);
    layout->addWidget(new QLabel("Point 2 (x2, y2):", this));
    layout->addWidget(x2LineEdit);
    layout->addWidget(y2LineEdit);
    layout->addWidget(findEquationButton);
    layout->addWidget(equationLabel);
    layout->addWidget(closeButton);
}

void LineFromTwoPointsDialog::findEquation()
{
    // Retrieve values from x1LineEdit, y1LineEdit, x2LineEdit, y2LineEdit
    QString x1Str = x1LineEdit->text();
    QString y1Str = y1LineEdit->text();
    QString x2Str = x2LineEdit->text();
    QString y2Str = y2LineEdit->text();

    // Convert the QString values to double
    bool ok;
    double x1 = x1Str.toDouble(&ok);
    double y1 = y1Str.toDouble(&ok);
    double x2 = x2Str.toDouble(&ok);
    double y2 = y2Str.toDouble(&ok);

    if (!ok) {
        // Handle the case where conversion fails (e.g., non-numeric input)
        qDebug() << "Invalid input. Please enter numeric values for x1, y1, x2, and y2.";
        return;
    }

    double slope = (y2 - y1)*1.0/(x2 - x1);
    double yIntercept = y1 - x1*slope;

    QString equation = QString("Equation: y = %1x + %2").arg(slope).arg(yIntercept);

    // Display the equation in your QLabel or wherever you want
    equationLabel->setText(equation);


    return;
}


void LineFromTwoPointsDialog::closeDialog()
{
    close();
}
