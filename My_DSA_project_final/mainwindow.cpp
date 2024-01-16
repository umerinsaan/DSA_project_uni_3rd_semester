#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->stackedWidget = new QStackedWidget;

    this->buttonsWidget = new ButtonsWidget;
    this->arithmeticWidget = new ArithmeticExpressionWidget;
    this->intersectionWidget = new IntersectionWidget;

    this->stackedWidget->addWidget(this->buttonsWidget);
    this->stackedWidget->addWidget(this->arithmeticWidget);
    this->stackedWidget->addWidget(this->intersectionWidget);

    // this->mainLayout = new QVBoxLayout;

    connectAll();

    this->setCentralWidget(this->stackedWidget);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::arithmetic_btn_handler()
{
    std::cout<<"SIGNAL RECEIEDADD"<<std::endl;
    this->stackedWidget->setCurrentIndex(1);
}

void MainWindow::resetStackedWidget()
{
    this->stackedWidget->setCurrentIndex(0);
}

void MainWindow::goToIntersectionPage(){
    std::cout<<"HER IAM"<<std::endl;
    this->stackedWidget->setCurrentIndex(2);
}

void MainWindow::connectAll()
{
    connect(this->buttonsWidget, &ButtonsWidget::arithmetic_btn_signal, this, &MainWindow::arithmetic_btn_handler);
    connect(this->buttonsWidget,&ButtonsWidget::intersection_btn_signal, this ,&MainWindow::goToIntersectionPage);
    connect(this->arithmeticWidget,&ArithmeticExpressionWidget::goBackClicked,this, &MainWindow::resetStackedWidget);
    connect(this->intersectionWidget,&IntersectionWidget::goBackClicked, this,& MainWindow::resetStackedWidget);
    return;
}
