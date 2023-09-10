#include "mainwindow.h"
#include "filesystemwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * w = new MainWindow;
    w->show();
    return a.exec();
}

/*
#include <QApplication>
#include "dependencies/QCustomPlot/qcustomplot.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Создание экземпляра QCustomPlot
    QCustomPlot *customPlot = new QCustomPlot;

    // Добавление QCustomPlot на форму
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(customPlot);
    widget->setLayout(layout);

    widget->show();

    return app.exec();
}*/