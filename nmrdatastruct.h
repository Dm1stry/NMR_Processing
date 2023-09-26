#ifndef NMRDATASTRUCT_H
#define NMRDATASTRUCT_H
#include <QVector>
#include <QMetaType>

struct NMRDataStruct
{
    QVector<double> A;
    QVector<double> t;
    QVector<double> p;
    QVector<double> pt;
};

Q_DECLARE_METATYPE(NMRDataStruct);

#endif