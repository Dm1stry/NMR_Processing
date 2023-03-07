#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "nmr_reader.hpp"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      x_scale(Scale::linear),
      y_scale(Scale::linear)
{
    ui->setupUi(this);
    // create graph and assign data to it:
    nmr_reader reader;
    NMR_Data_1D CPMG = reader.Read("/home/peter/Documents/CPMG_X_10_10S_4000TAU_1000ECHO.nmr");
    auto customPlot = (ui->plot);
    customPlot->addGraph();
    customPlot->graph(0)->setData(CPMG.t, CPMG.A);
    // give the axes some labels:
    customPlot->xAxis->setLabel("t");
    customPlot->yAxis->setLabel("A(t)");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, *(std::max_element(CPMG.t.begin(), CPMG.t.end())));
    customPlot->yAxis->setRange(0, *(std::max_element(CPMG.A.begin(), CPMG.A.end())));
    customPlot->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}


inline void MainWindow::on_ScaleBox_textHighlighted(const QString &param, Scale &scale)
{
    if(param == "Линейная")
    {
        scale = Scale::linear;
    }
    else if(param == "Логарифмическая")
    {
        scale = Scale::log;
    }
}


void MainWindow::on_xScaleBox_textHighlighted(const QString &param)
{
    on_ScaleBox_textHighlighted(param, x_scale);
    if(param == "Линейная")
    {
        ui->plot->xAxis->setScaleType(QCPAxis::stLinear);
    }
    else if(param == "Логарифмическая")
    {
        ui->plot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    }
    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_yScaleBox_textHighlighted(const QString &param)
{
    on_ScaleBox_textHighlighted(param, y_scale);
    if(param == "Линейная")
    {
        ui->plot->yAxis->setScaleType(QCPAxis::stLinear);
    }
    else if(param == "Логарифмическая")
    {
        ui->plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    }
    ui->plot->rescaleAxes();
    ui->plot->replot();
}
