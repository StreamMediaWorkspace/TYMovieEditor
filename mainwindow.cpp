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
    static int index = 0;
    std::string name = "";
    if (index%2 == 0) {
        name = "D:\\code\\mycode\\TYMovieEditor\\80s_test_bd.mp4";
    } else {
        name = "D:\\code\\mycode\\TYMovieEditor\\BLACKPINK_Kill_This_Love.mp4";
    }
    index++;
    ui->movieWidget->open(name);
}

MainWindow::~MainWindow()
{
    delete ui;
}
