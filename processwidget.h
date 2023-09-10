#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include <QTabWidget>

#include "tikhonovprocesswidget.h"


class ProcessWidget : public QTabWidget
{
Q_OBJECT
public:
    ProcessWidget(QWidget * patent = nullptr);
private:
    QVector<BaseProcessWidget *> widgets_;    
};

#endif