#ifndef BASEPROCESSOR_H
#define BASEPROCESSOR_H

#include <QObject>
#include <QPair>
#include <QVector>

#include "nmrdatastruct.h"

class BaseProcessor : public QObject
{
Q_OBJECT
public:
    BaseProcessor(QObject * parent = nullptr);
public slots:
    virtual void Process() = 0;
    virtual void updateParameter(QString parameter_name, QVariant parameter_value) = 0;
    virtual void updateData(const NMRDataStruct& raw_data) = 0;
signals:
    void processingStarted();
    void processingStateUpdate(const uchar&);  // Processing state in percentages
    void processingDone(const NMRDataStruct&);
};

#endif