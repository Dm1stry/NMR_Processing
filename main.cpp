#include "widgets/mainwindow.h"
#include "widgets/filesystemwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * w = new MainWindow;
    w->show();
    return a.exec();
}