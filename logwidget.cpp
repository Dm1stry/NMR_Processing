#include "logwidget.h"

LogWidget::LogWidget(QWidget* parent)
  : QPlainTextEdit(parent)
{
    this->setReadOnly(true);
    this->printLog("Программа запущена");
}

void LogWidget::printLog(const QString& information)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm");
    this->appendPlainText(timestamp + " " + information);
}