#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include <QTabWidget>

#include "tikhonovprocesswidget.h"
#include "sequentalprocesswidget.h"
#include "nmrdatastruct.h"


class ProcessWidget : public QTabWidget
{
Q_OBJECT
public:
    ProcessWidget(QWidget * patent = nullptr);
    void addProcessWidget(BaseProcessWidget * widget);
private:
    QVector<BaseProcessWidget *> widgets_;
public slots:
    void updateData(const NMRDataStruct& raw_data);
signals:
    Q_SIGNAL void processingDone(const NMRDataStruct& processed_data);
    Q_SIGNAL void componentsFound(const NMRDataStruct& components);
    Q_SIGNAL void clearData();
};

#endif