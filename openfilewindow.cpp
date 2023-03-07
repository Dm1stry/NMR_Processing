#include "openfilewindow.h"
#include "ui_openfilewindow.h"

OpenFileWindow::OpenFileWindow(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::OpenFileWindow)
{
    ui_->setupUi(this);
}

OpenFileWindow::~OpenFileWindow()
{
    delete ui_;
}

void OpenFileWindow::on_open_file_explorer_clicked()
{
    QString runPath = QCoreApplication::applicationDirPath(); // Get the root path of the project
    QString file_name = QFileDialog::getOpenFileName(this,QStringLiteral("Select a document"),runPath,"Any(*.*)",nullptr, QFileDialog::DontResolveSymlinks);
    ui_->file_path->setText(file_name);
    file_path_ = file_name;
}


void OpenFileWindow::on_data_type_box_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        data_type_ = ExperimentType::CPMG;
        break;
    case 1:
        data_type_ = ExperimentType::T1ir;
        break;
    case 2:
        data_type_ = ExperimentType::T2dfi;
        break;
    }
}

void OpenFileWindow::setDataPtr(Data *data_ptr)
{
    data_ptr_ = data_ptr;
}

void OpenFileWindow::on_open_file_button_clicked()
{
    if(data_type_ == ExperimentType::CPMG)
    {
        data_ptr_->readAsCPMG(file_path_);
    }
    this->close();
}

