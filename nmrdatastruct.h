#ifndef NMRDATASTRUCT_H
#define NMRDATASTRUCT_H
#include <QVector>

struct NMRDataStruct
{
    QVector<double> A;
    QVector<double> t;
    QVector<double> p;
    QVector<double> pt;
};

#endif