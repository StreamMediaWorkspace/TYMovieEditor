#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->postionSlider, SIGNAL(valueChanged(int)), this, SLOT(onPositionChanged(int)));
}

void MainWindow::onPositionChanged(int pos){
    ui->movieWidget->setPosition(pos);
}

MainWindow::~MainWindow()
{
    delete ui;
}
