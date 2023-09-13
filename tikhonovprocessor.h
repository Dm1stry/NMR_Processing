#ifndef TIKHONOVPROCESSOR_H
#define TIKHONOVPROCESSOR_H

#include <Eigen/Dense>

#include "baseprocessor.h"


class TikhonovProcessor : public BaseProcessor
{
Q_OBJECT
public:
    TikhonovProcessor(QObject * parent = nullptr);

    virtual void Process();
    virtual void setParameter(QPair<QString, double> parameter);

private:
    double alpha_;
    size_t iterations_;
    double T_min_;
    double T_max_;
    size_t p_size_;

signals:

};

#endif