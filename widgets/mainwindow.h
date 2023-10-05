#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMetaType>


#include "filesystemwidget.h"
#include "processwidget.h"
#include "logwidget.h"
#include "plotwidget.h"
#include "nmrdata.h"
#include "nmrdatastruct.h"

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
    PlotWidget * noise_widget_;
    ProcessWidget * process_widget_;

    inline void connections();
    inline void layoutSetup();
};

#endif