#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "nmr_reader.hpp"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // create graph and assign data to it:
    nmr_reader reader;
    NMR_Data_1D CPMG = reader.Read("/home/peter/Documents/CPMG_X_10_10S_4000TAU_1000ECHO.nmr");
    auto customPlot = (ui->plot);
    customPlot->addGraph();
    customPlot->graph(0)->setData(CPMG.t, CPMG.A);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, *(std::max_element(CPMG.t.begin(), CPMG.t.end())));
    customPlot->yAxis->setRange(0, *(std::max_element(CPMG.A.begin(), CPMG.A.end())));
    customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

