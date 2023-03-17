#ifndef TIKHONOVPROCESSOR_H
#define TIKHONOVPROCESSOR_H
#include "iprocessor.h"
#include <eigen3/Eigen/Dense>
#include <cmath>
#include <algorithm>

class TikhonovProcessor : public iProcessor
{
public:
    TikhonovProcessor();
    void Process(Data& data);
    QPair<QVector<double>, QVector<double>> getApproximatedCurve() const;
    QPair<QVector<double>, QVector<double>>  getSpectrum() const;
    ~TikhonovProcessor();
private:
    Eigen::MatrixXd * K_;
    Eigen::VectorXd * s_;
    Eigen::VectorXd * r_;
    QVector<double> t_;
    double alfa_;
};

#endif // TIKHONOVPROCESSOR_H
