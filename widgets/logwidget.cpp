#include "logwidget.h"

LogWidget::LogWidget(QWidget* parent)
  : QPlainTextEdit(parent)
{
    this->setReadOnly(true);
    this->printLog("Программа запущена");
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
}

void LogWidget::printLog(const QString& information, bool timestamp_needed)
{
    QString output = "";
    if(timestamp_needed)
    {
        output = QDateTime::currentDateTime().toString("hh:mm");
    }
    output += " " + information;
    this->appendPlainText(output);
}

void LogWidget::printComponents(const NMRDataStruct& components)
{
	this->printLog("");
	for(int i = 0; i < components.A.size(); ++i)
	{
		QString number = QString::number(i + 1);
		QString component_string = "A" + number + ": " + QString::number(components.A[i]) + ", T" + number + ": " + QString::number(components.t[i]);
		this->printLog(component_string, false);
	}
}