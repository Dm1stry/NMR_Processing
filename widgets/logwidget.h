#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QPlainTextEdit>
#include <QDateTime>

class LogWidget : public QPlainTextEdit
{
Q_OBJECT
public:
    LogWidget(QWidget * parent = nullptr);
public slots:
    void printLog(const QString& information);
};

#endif