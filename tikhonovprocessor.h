#ifndef TIKHONOVPROCESSOR_H
#define TIKHONOVPROCESSOR_H
#include "iprocessor.h"
#include <eigen3/Eigen/Dense>

class TikhonovProcessor : public iProcessor
{
public:
    TikhonovProcessor();
    void Process(const Data& data);
    QPair<QVector<double>, QVector<double>> getApproximatedCurve();
    QPair<QVector<double>, QVector<double>>  getSpectrum();
    ~TikhonovProcessor();
private:
    Eigen::MatrixXd * K_;
    Eigen::VectorXd * s_;
    Eigen::VectorXd * r_;
    Eigen::VectorXd * t_;
    double alfa_;
};

#endif // TIKHONOVPROCESSOR_H
