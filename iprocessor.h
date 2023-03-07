#ifndef IPROCESSOR_H
#define IPROCESSOR_H
#include "data.h"

class iProcessor
{
public:
    virtual void Process(const Data& data) = 0;
    virtual QPair<QVector<double>, QVector<double>> getApproximatedCurve() const = 0;
    virtual QPair<QVector<double>, QVector<double>>  getSpectrum() const = 0;
    virtual ~iProcessor() = default;
};

#endif // IPROCESSOR_H
