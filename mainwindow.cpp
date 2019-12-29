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
#ifdef WIN32
    if (index%2 == 0) {
        name = ".\\80s_test_bd.mp4";
    } else {
        name = ".\\BLACKPINK_Kill_This_Love.mp4";
    }
#else
    if (index%2 == 1) {
        name = "/Users/admin/Downloads/project/TYMovieEditor/80s_test_bd.mp4";
    } else {
        name = "/Users/admin/Downloads/project/TYMovieEditor/BLACKPINK_Kill_This_Love.mp4";
    }
#endif
    index++;
    ui->movieWidget->open(name);
}

MainWindow::~MainWindow()
{
    delete ui;
}
