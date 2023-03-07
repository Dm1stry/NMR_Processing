#ifndef IPROCESSOR_H
#define IPROCESSOR_H
#include "data.h"

class iProcessor
{
public:
    iProcessor();
    virtual void Process(const Data& data);
    virtual QPair<QVector<double>, QVector<double>> getApproximatedCurve();
    virtual QPair<QVector<double>, QVector<double>>  getSpectrum();
    virtual ~iProcessor();
};

#endif // IPROCESSOR_H
