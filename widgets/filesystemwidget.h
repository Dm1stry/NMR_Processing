#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QFileSystemModel>
#include <QFileDialog>
#include <QFileInfo>
#include <QTreeView>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>

class FileSystemWidget : public QWidget
{
Q_OBJECT
public:
    FileSystemWidget(QWidget * parent = nullptr);

private:
    QFileSystemModel * filesystem_model_;
    QTreeView * filesystem_view_;
    QLineEdit * directory_edit_;
    QPushButton * directory_explorer_button_;

    QFileDialog * directory_explorer_;

    QDir current_directory_;

    void onPathSelected(const QString& path);

signals:
    void fileSelected(const QString&);

public slots:
    void changeDirectory(const QString& directory_path);
    void openDirectoryExplorer();
    void loadSettings();
    void saveSettings();   
};

#endif