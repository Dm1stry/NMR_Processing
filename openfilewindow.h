#ifndef OPENFILEWINDOW_H
#define OPENFILEWINDOW_H

#include <QWidget>
#include <QDir>
#include <QUrl>
#include <QFileDialog>

#include "data.h"

namespace Ui {
class OpenFileWindow;
}

class OpenFileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OpenFileWindow(QWidget *parent = nullptr);
    void setDataPtr(Data * data_ptr);
    ~OpenFileWindow();

private slots:
    void on_open_file_explorer_clicked();

    void on_data_type_box_currentIndexChanged(int index);

    void on_open_file_button_clicked();

private:
    Ui::OpenFileWindow *ui_;
    QString file_path_;
    ExperimentType data_type_;
    Data * data_ptr_;
};

#endif // OPENFILEWINDOW_H
