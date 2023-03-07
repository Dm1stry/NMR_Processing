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
    QString file_name = QFileDialog::getOpenFileName(this,QStringLiteral("Select a document"),runPath,"Text Files(*.txt)",nullptr, QFileDialog::DontResolveSymlinks);
    ui_->file_path->setText(file_name);
}

