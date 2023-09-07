#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "filesystemwidget.h"
#include "logwidget.h"

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget * parent = nullptr);
private:
    FileSystemWidget * filesystem_widget_;
    LogWidget * log_widget_;
};

#endif