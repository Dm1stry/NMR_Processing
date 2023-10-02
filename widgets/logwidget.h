#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QPlainTextEdit>
#include <QDateTime>

#include "nmrdatastruct.h"

class LogWidget : public QPlainTextEdit
{
Q_OBJECT
public:
    LogWidget(QWidget * parent = nullptr);
public slots:
    void printLog(const QString& information, bool timestamp_needed = true);
    void printComponents(const NMRDataStruct& components);
};

#endif