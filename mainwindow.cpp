#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->postionSlider, SIGNAL(valueChanged(int)), this, SLOT(onChangPosition(int)));
    connect(ui->btnChangedMovie, SIGNAL(clicked(bool)), SLOT(onChangeMovieClick()));

    //connect(ui->movieWidget, SIGNAL(PositionChanged(unsigned long long)), this, SLOT(onPositionChanged(unsigned long long)));
}

void MainWindow::onChangPosition(int pos) {
    ui->movieWidget->setPosition(pos);
}

void MainWindow::onPositionChanged(unsigned long long pos){
    if (pos != ui->postionSlider->value()) {
        ui->postionSlider->setValue(pos);
    }
}

void MainWindow::onChangeMovieClick() {
    static int index = 0;
    std::string name = "";
    Json::Value *fileInfo = nullptr;
#ifdef WIN32
    if (index%2 == 0) {
        name = "../80s_test_bd.mp4";
    } else {
        name = "../BLACKPINK_Kill_This_Love.mp4";
    }
#else
    if (index%2 == 1) {
        name = "/Users/admin/Downloads/project/TYMovieEditor/80s_test_bd.mp4";
    } else {
        name = "/Users/admin/Downloads/project/TYMovieEditor/BLACKPINK_Kill_This_Love.mp4";
    }
#endif
    index++;
    QHash<QString, Json::Value*>::Iterator it = m_fileHash.find(name.c_str());
    if (it == m_fileHash.end()) {
        fileInfo = new Json::Value();
        (*fileInfo)["name"] = name;
        (*fileInfo)["position"] = 0;
        m_fileHash.insert(name.c_str(), fileInfo);
    } else {
        fileInfo = it.value();
    }
    ui->movieWidget->open(fileInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}
