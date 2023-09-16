#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>


#include "filesystemwidget.h"
#include "processwidget.h"
#include "logwidget.h"
#include "plotwidget.h"
#include "nmrdata.h"

class MainWindow : public QWidget
{
Q_OBJECT
public:
    MainWindow(QWidget * parent = nullptr);
private:
    NMRData * data_;
    FileSystemWidget * filesystem_widget_;
    LogWidget * log_widget_;
    PlotWidget * plot_widget_;
    PlotWidget * spectrum_widget_;
    ProcessWidget * process_widget_;
};

#endif