#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent)
  : QWidget(parent),
    filesystem_widget_(new FileSystemWidget),
    process_widget_(new ProcessWidget),
    log_widget_(new LogWidget),
    plot_widget_(new PlotWidget),
    spectrum_widget_(new PlotWidget)
{
    QHBoxLayout * main_layout = new QHBoxLayout;

    QVBoxLayout * left_layout = new QVBoxLayout;
    QVBoxLayout * mid_layout = new QVBoxLayout;
    QVBoxLayout * right_layout = new QVBoxLayout;

    left_layout->addWidget(this->filesystem_widget_);
    left_layout->addWidget(this->log_widget_);

    mid_layout->addWidget(this->process_widget_);

    right_layout->addWidget(this->plot_widget_);
    right_layout->addWidget(this->spectrum_widget_);

    main_layout->addLayout(left_layout);
    main_layout->addLayout(mid_layout);
    main_layout->addLayout(right_layout);

    this->setLayout(main_layout);
}