#include "buttonswidget.h"
#include <iostream>


ButtonsWidget::ButtonsWidget(QWidget *parent)
    : QWidget{parent}
{
    this->mainLayout = new QVBoxLayout;

    this->arithmetic_btn = new QPushButton("Solve Arithmetic Expression");

    this->intersectionOfTwoLines_btn = new QPushButton("Find intersection of two lines");

    this->lineFromTwoPoints_btn = new QPushButton("Find line from two points");

    this->lineFromTwoPointsDialog = new LineFromTwoPointsDialog;

    this->mainLayout->addWidget(this->arithmetic_btn);
    this->mainLayout->addWidget(this->intersectionOfTwoLines_btn);
    this->mainLayout->addWidget(this->lineFromTwoPoints_btn);

    this->setLayout(this->mainLayout);

    connect(this->arithmetic_btn, &QPushButton::clicked, this, &ButtonsWidget::arithmetic_btn_slot);
    connect(this->intersectionOfTwoLines_btn, &QPushButton::clicked, this, &ButtonsWidget::intersection_btn_slot);
    connect(this->lineFromTwoPoints_btn,&QPushButton::clicked, this,&ButtonsWidget::openLineFromTwoPointsDialog);
}

void ButtonsWidget::arithmetic_btn_slot()
{
    std::cout<<"In btnccp"<<std::endl;
    emit this->arithmetic_btn_signal();
}

void ButtonsWidget::intersection_btn_slot()
{
    emit this->intersection_btn_signal();
}

void ButtonsWidget::openLineFromTwoPointsDialog()
{
    this->lineFromTwoPointsDialog->exec();
}
