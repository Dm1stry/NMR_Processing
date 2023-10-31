#ifndef SEQUENTALPROCESSOR_H
#define SEQUENTALPROCESSOR_H

#include "baseprocessor.h"
#include "approximation.h"
#include "mathfunctions.h"
#include <vector>

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

    std::vector<double> params_;
    QVector<double> A_appr_;
    QVector<double> pt_;
    QVector<double> p_;

    uint N_max_;
    double T_min_;
    double T_max_;

    void createSpectrum(NMRDataStruct& processed_data);
    bool approximationIsGoodEnough(const std::vector<double>& prev, const appr_funcs::approximation_data& data);

};

#endif