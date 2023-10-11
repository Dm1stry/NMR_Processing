#ifndef SEQUENTALPROCESSOR_H
#define SEQUENTALPROCESSOR_H

#include "baseprocessor.h"


class SequentalProcessor : public BaseProcessor
{
Q_OBJECT
public:
    SequentalProcessor(QObject * parent = nullptr);
    ~SequentalProcessor();

    /*virtual*/ void Process();
    /*virtual*/ void updateParameter(QString parameter_name, QVariant parameter_value);
    /*virtual*/ void updateData(const NMRDataStruct& raw_data);
private:
    QVector<double> t_;
    QVector<double> A_;

    QVector<double> A_appr_;
    QVector<double> pt_;
    QVector<double> p_;

    uint N_max_;
};

#endif