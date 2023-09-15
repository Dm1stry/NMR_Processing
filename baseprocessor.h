#ifndef BASEPROCESSOR_H
#define BASEPROCESSOR_H

#include <QObject>
#include <QPair>
#include <QVector>

class BaseProcessor : public QObject
{
Q_OBJECT
public:
    BaseProcessor(QObject * parent = nullptr);
public slots:
    virtual void Process() = 0;
    virtual void setParameter(QPair<QString, double>) = 0;
    virtual void updateData(QVector<double> t, QVector<double> A) = 0;
signals:
    void processingStarted();
    void processingStateUpdate(int);
    void processingDone();
};

#endif