#ifndef TIKHONOVPROCESSOR_H
#define TIKHONOVPROCESSOR_H

#include <Eigen/Dense>
#include <cmath>
#include <vector>

#include "baseprocessor.h"


class TikhonovProcessor : public BaseProcessor
{
Q_OBJECT
public:
    TikhonovProcessor(QObject * parent = nullptr);

    virtual void Process();
    virtual void setParameter(QPair<QString, double> parameter);
    virtual void updateData(QVector<double> t, QVector<double> A);

private:
    double alpha_;
    uint iterations_;
    double T_min_;
    double T_max_;
    uint p_size_;

    QVector<double> t_;
    QVector<double> A_;

    QVector<double> A_appr_;
    QVector<double> pt_;
    QVector<double> p_;
};

#endif