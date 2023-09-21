#include "filesystemwidget.h"

FileSystemWidget::FileSystemWidget(QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    filesystem_model_(new QFileSystemModel(this)),
    filesystem_view_(new QTreeView()),
    directory_edit_(new QLineEdit),
    directory_explorer_button_(new QPushButton("...")),
    directory_explorer_(new QFileDialog(this)),
    current_directory_(QDir::rootPath())
{
    QVBoxLayout * widget_layout = new QVBoxLayout();

    QHBoxLayout * directory_edit_layout = new QHBoxLayout();

    directory_edit_layout->addWidget(this->directory_edit_);
    directory_edit_layout->addWidget(this->directory_explorer_button_);

    widget_layout->addLayout(directory_edit_layout);

    this->filesystem_model_->setRootPath(QDir::rootPath());
    this->filesystem_view_->setModel(this->filesystem_model_);
    this->filesystem_view_->hideColumn(1);
    this->filesystem_view_->hideColumn(3);
    widget_layout->addWidget(this->filesystem_view_);

    this->setLayout(widget_layout);

    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    this->directory_explorer_->setFileMode(QFileDialog::ExistingFile);
    this->changeDirectory(this->filesystem_model_->myComputer().toString());

    //Open Directory Explorer on it's button
    connect(this->directory_explorer_button_, &QPushButton::clicked, this, &FileSystemWidget::openDirectoryExplorer);
    //If directory selected - change dir to it, if file - emit signal, that file selected
    connect(this->filesystem_view_, &QTreeView::doubleClicked, [=](){
        this->onPathSelected(this->filesystem_model_->filePath(this->filesystem_view_->currentIndex()));
    });

    connect(this->directory_edit_, &QLineEdit::returnPressed, [=](){this->changeDirectory(this->directory_edit_->text());});
}

void FileSystemWidget::changeDirectory(const QString& directory_path)
{
    QDir directory(directory_path);
    if(directory.exists(directory_path))
    {
        current_directory_ = directory;
        filesystem_view_->setRootIndex(filesystem_model_->index(directory_path));
        this->directory_edit_->setText(directory_path);
    }
}

void FileSystemWidget::openDirectoryExplorer()
{
    this->directory_explorer_->setDirectory(current_directory_);
    if(this->directory_explorer_->exec())
    {
        this->onPathSelected(directory_explorer_->selectedFiles()[0]);
    }
}

void FileSystemWidget::onPathSelected(const QString& path)
{
    QFileInfo info(path);
    if(info.isDir())
    {
        this->changeDirectory(path);
    }
    else
    {
        this->changeDirectory(info.absoluteDir().absolutePath());
        emit fileSelected(path);
    }
}