#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      data(new Data),
      x_scale(Scale::linear),
      y_scale(Scale::linear)
{
    ui->setupUi(this);
    auto plot = (ui->plot_widget);
    auto spectrum = (ui->spectrum_widget);
    data->readFictiveData();  //Фиктивное чтение данных
    ui->plot_widget->addGraph();
    /*ui->plot_widget->graph(0)->setData(data->getTimes(), data->getAmplitudes());
    plot->graph(0)->rescaleAxes();
    plot->replot();
    */
    redrawGraphs();
}

MainWindow::~MainWindow()
{
    delete data;
    delete open_file_window;
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
        ui->plot_widget->xAxis->setScaleType(QCPAxis::stLinear);
    }
    else if(param == "Логарифмическая")
    {
        ui->plot_widget->xAxis->setScaleType(QCPAxis::stLogarithmic);
    }
    ui->plot_widget->rescaleAxes();
    ui->plot_widget->replot();
}

void MainWindow::on_yScaleBox_textHighlighted(const QString &param)
{
    on_ScaleBox_textHighlighted(param, y_scale);
    if(param == "Линейная")
    {
        ui->plot_widget->yAxis->setScaleType(QCPAxis::stLinear);
    }
    else if(param == "Логарифмическая")
    {
        ui->plot_widget->yAxis->setScaleType(QCPAxis::stLogarithmic);
    }
    ui->plot_widget->rescaleAxes();
    ui->plot_widget->replot();
}

void MainWindow::on_open_file_triggered()
{
    open_file_window = new OpenFileWindow();
    open_file_window->setDataPtr(data);
    open_file_window->show();
    //ui->plot_widget->addGraph();
    //ui->plot_widget->graph(0)->setData(data->getTimes(), data->getAmplitudes());
}

void MainWindow::on_tikhonov_process_button_clicked()
{
    if(data != nullptr)
    {
        tikhonov.Process(*data);
        ui->plot_widget->addGraph();
        redrawGraphs();
    }

}

void MainWindow::redrawGraphs()
{
    ui->plot_widget->graph(0)->setData(data->getTimes(), data->getAmplitudes());
    ui->plot_widget->graph(0)->rescaleAxes();
    ui->plot_widget->replot();
}

