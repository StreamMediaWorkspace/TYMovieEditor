#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <Json.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onChangPosition(int pos);
    void onPositionChanged(unsigned long long);
    void onChangeMovieClick();

private:
    Ui::MainWindow *ui;

    QHash<QString, Json::Value*> m_fileHash;
};

#endif // MAINWINDOW_H
