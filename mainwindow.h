#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "data.h"
#include "iprocessor.h"
#include "tikhonovprocessor.h"
#include "openfilewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class Scale{
    log,
    linear
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_xScaleBox_textHighlighted(const QString &param);
    void on_yScaleBox_textHighlighted(const QString &param);
    void on_open_file_triggered();


private:
    inline void on_ScaleBox_textHighlighted(const QString &param, Scale &scale);
    Ui::MainWindow *ui;
    Data * data;
    iProcessor * processors[3];
    Scale x_scale;
    Scale y_scale;
    OpenFileWindow * open_file_window;
};
#endif // MAINWINDOW_HPP
