#include "mainwindow.h"
#include <eigen3/Eigen/Dense>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
