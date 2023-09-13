#ifndef TIKHONOVPROCESSOR_H
#define TIKHONOVPROCESSOR_H

#include "baseprocessor.h"

class TikhonovProcessor : public BaseProcessor
{
Q_OBJECT
public:
    TikhonovProcessor(QObject * parent = nullptr);

    virtual void Process();
    virtual void setParameter(QPair<QString, double> parameter);
};

#endif