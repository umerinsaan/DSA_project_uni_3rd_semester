#include "intersectionwidget.h"

IntersectionWidget::IntersectionWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void IntersectionWidget::setupUI()
{
    equationLabel = new QLabel("Equation 1:", this);
    equation2Label = new QLabel("Equation 2:", this);
    equationLineEdit = new QLineEdit(this);
    equation2LineEdit = new QLineEdit(this);
    findIntersectionButton = new QPushButton("Find Intersection", this);
    xCoordinateLabel = new QLabel("X Coordinate:", this);
    yCoordinateLabel = new QLabel("Y Coordinate:", this);
    goBackButton = new QPushButton("Go Back", this);

    connect(findIntersectionButton, &QPushButton::clicked, this, &IntersectionWidget::findIntersection);
    connect(goBackButton, &QPushButton::clicked, this, &IntersectionWidget::onGoBackClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(equationLabel);
    layout->addWidget(equationLineEdit);
    layout->addWidget(equation2Label);
    layout->addWidget(equation2LineEdit);
    layout->addWidget(findIntersectionButton);
    layout->addWidget(xCoordinateLabel);
    layout->addWidget(yCoordinateLabel);
    layout->addStretch(1);
}

void IntersectionWidget::findIntersection()
{
    long double a1 = 0,a2 = 0,b1 = 0,b2 = 0,c1 = 0 ,c2 = 0,x ,y;

    QString eq1 = this->equationLineEdit->text();

    unsigned long long i=0;
    bool isNegative = false;
    while(i<eq1.length() && eq1[i] != 'x'){
        if(eq1[i] == '-') isNegative = true;
        a1 = a1*10 + (eq1[i].toLatin1() - '0');
        i++;
    }

    if(isNegative){
        a1 = -a1;
    }

    isNegative = false;
    while(i<eq1.length() && !(eq1[i]>='0' && eq1[i]<='9')){
        if(eq1[i] == '-'){
            isNegative = true;
        }
        i++;
    }

    while(i<eq1.length() && eq1[i]!='y'){
        b1 = b1*10 + (eq1[i].toLatin1()-'0');
        i++;
    }

    if(isNegative){
        b1 = -b1;
    }

    isNegative = false;
    while(i<eq1.length() && !(eq1[i]>='0' && eq1[i]<='9')){
        if(eq1[i] == '-') isNegative = true;
        i++;
    }

    while(i<eq1.length() && eq1[i]>='0' && eq1[i]<='9'){
        c1 = c1*10 + (eq1[i].toLatin1()-'0');
        i++;
    }

    if(isNegative) c1 = -c1;
    isNegative = false;


    QString eq2 = this->equation2LineEdit->text();

    i=0;
    while(i<eq2.length() && eq2[i] != 'x'){
        if(eq2[i] == '-') isNegative = true;
        a2 = a2*10 + (eq2[i].toLatin1() - '0');
        i++;
    }

    if(isNegative){
        a2 = -a2;
    }

    isNegative = false;
    while(i<eq2.length() && !(eq2[i]>='0' && eq2[i]<='9')){
        if(eq2[i] == '-'){
            isNegative = true;
        }
        i++;
    }

    while(i<eq2.length() && eq2[i]!='y'){
        b2 = b2*10 + (eq2[i].toLatin1()-'0');
        i++;
    }

    if(isNegative){
        b2 = -b2;
    }

    isNegative = false;
    while(i<eq2.length() && !(eq2[i]>='0' && eq2[i]<='9')){
        if(eq2[i] == '-') isNegative = true;
        i++;
    }

    while(i<eq2.length() && eq2[i]>='0' && eq2[i]<='9'){
        c2 = c2*10 + (eq2[i].toLatin1()-'0');
        i++;
    }

    if(isNegative) c2 = -c2;
    isNegative = false;


    std::cout<<"a1 = "<<a1<<std::endl;
    std::cout<<"a2 = "<<a2<<std::endl;
    std::cout<<"b1 = "<<b1<<std::endl;
    std::cout<<"b2 = "<<b2<<std::endl;
    std::cout<<"c1 = "<<c1<<std::endl;
    std::cout<<"c2 = "<<c2<<std::endl;


    x = (c1*b2 - c2*b1)*1.0 / (a1*b2 - a2*b1);

    y = (a2*c1 - a1*c2)*1.0 / (a2*b1 - a1*b2);


    xCoordinateLabel->setText("X Coordinate: " + QString::fromStdString(std::to_string(x)));
    yCoordinateLabel->setText("Y Coordinate: " + QString::fromStdString(std::to_string(y)));
}

void IntersectionWidget::onGoBackClicked()
{
    emit goBackClicked();
}
