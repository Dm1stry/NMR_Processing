#ifndef NMRDATA_H
#define NMRDATA_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QRegExp>

#include "nmrdatastruct.h"


class NMRData : public QObject
{
Q_OBJECT
public:
    NMRData(QObject * parent = nullptr);
private:
    QVector<double> A_;
    QVector<double> t_;
    QVector<double> A_approximated_;
    QVector<double> t_approximated_;
    QVector<double> p_;
    QVector<double> pt_;

public slots:
    void readAsCPMG(const QString& filepath);
    void setRawData(const NMRDataStruct& raw_data);
    void setProcessedData(const NMRDataStruct& processed_data);
    void clearRawData();
    void clearProcessedData();
    void clearData();
    
signals:
    Q_SIGNAL void wrongData();
    Q_SIGNAL void rawDataUpdated(const NMRDataStruct&);
    Q_SIGNAL void processedDataUpdated(const NMRDataStruct&);
    Q_SIGNAL void rawDataCleared();
    Q_SIGNAL void processedDataCleared();
    //void clearData();
};

#endif