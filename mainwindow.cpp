#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->postionSlider, SIGNAL(valueChanged(int)), this, SLOT(onPositionChanged(int)));
    connect(ui->btnChangedMovie, SIGNAL(clicked(bool)), SLOT(onChangeMovieClick()));
}

void MainWindow::onPositionChanged(int pos){
    ui->movieWidget->setPosition(pos);
}

void MainWindow::onChangeMovieClick() {
    ui->movieWidget->open(std::string("C:\\Users\\TAL\\Music\\MV\\BLACKPINK-Kill This Love(标清).mp4"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
