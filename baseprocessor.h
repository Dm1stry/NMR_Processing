#ifndef BASEPROCESSOR_H
#define BASEPROCESSOR_H

#include <QObject>
#include <QPair>
#include <QVector>
#include <QVariant>
#include <QString>

#include "nmrdatastruct.h"
#include "iloggable.h"

class BaseProcessor : public QObject //, public ILoggable
{
Q_OBJECT
public:
    BaseProcessor(QObject * parent = nullptr);
public slots:
    virtual void Process() = 0;
    virtual void updateParameter(QString parameter_name, QVariant parameter_value) = 0;
    virtual void updateData(const NMRDataStruct& raw_data) = 0;
    void clearData();
signals:
    Q_SIGNAL void processingStarted();
    Q_SIGNAL void processingStateUpdate(const int&);  // Processing state in percentages
    Q_SIGNAL void processingDone(const NMRDataStruct&);
};

#endif