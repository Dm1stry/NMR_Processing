#ifndef BASEPROCESSOR_H
#define BASEPROCESSOR_H

#include <QObject>
#include <QPair>

class BaseProcessor : public QObject
{
Q_OBJECT
public:
    BaseProcessor(QObject * parent = nullptr);
public slots:
    virtual void Process() = 0;
    virtual void setParameter(QPair<QString, double>) = 0;
signals:
    void processingStateUpdate(int);
    void processingDone();
};

#endif