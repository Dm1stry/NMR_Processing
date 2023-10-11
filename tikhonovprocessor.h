#ifndef TIKHONOVPROCESSOR_H
#define TIKHONOVPROCESSOR_H

#//include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <algorithm>
#include <QCoreApplication>
#include <QVector>

#include "baseprocessor.h"
#include "mathfunctions.h"



class TikhonovProcessor : public BaseProcessor
{
Q_OBJECT
public:
    TikhonovProcessor(QObject * parent = nullptr);
    ~TikhonovProcessor();

    /*virtual*/ void Process() Q_DECL_OVERRIDE;
    /*virtual*/ void updateParameter(QString parameter_name, QVariant parameter_value) Q_DECL_OVERRIDE;
    /*virtual*/ void updateData(const NMRDataStruct& raw_data) Q_DECL_OVERRIDE;

private:
    NMRDataStruct convert_spectrum(NMRDataStruct& processed_data);
    inline void getComponents(const NMRDataStruct& processed_data);
    inline double find_peak_S(const size_t& peak_index, std::vector<size_t> minimums);
    inline void getNoise(NMRDataStruct& components);

    inline void enlargeMemory(const uint& p_size, const uint& t_size);
    inline double * getMemory(const size_t& size);
    inline void clearMemory();

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

    double * memory_;
    double * first_free_cell_;
    size_t memory_size_;
};

#endif