#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent)
  : QWidget(parent),
    filesystem_widget_(new FileSystemWidget),
    log_widget_(new LogWidget)
{
    QHBoxLayout * main_layout = new QHBoxLayout;

    main_layout->addWidget(filesystem_widget_);
    main_layout->addWidget(log_widget_);

    this->setLayout(main_layout);
}