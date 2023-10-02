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
    QVector<double> A_;  // Raw NMR data
    QVector<double> t_;  // NMR data time
    QVector<double> A_approximated_;  // Processed NMR data
    QVector<double> t_approximated_;  // Time of processed NMR data
    QVector<double> p_;  // NMR spectrum
    QVector<double> pt_;  // NMR spectrum times

    QVector<double> M_;  //Component ratio
    QVector<double> T_;  //Component times

public slots:
    void readAsCPMG(const QString& filepath);
    void setRawData(const NMRDataStruct& raw_data);
    void setProcessedData(const NMRDataStruct& processed_data);
    void setComponents(const NMRDataStruct& processed_data);
    void clearRawData();
    void clearProcessedData();
    void clearComponents();
    void clearData();
    
signals:
    Q_SIGNAL void wrongData();
    Q_SIGNAL void rawDataUpdated(const NMRDataStruct&);
    Q_SIGNAL void processedDataUpdated(const NMRDataStruct&);
    Q_SIGNAL void componentsUpdated(const NMRDataStruct&);
    Q_SIGNAL void rawDataCleared();
    Q_SIGNAL void processedDataCleared();
    Q_SIGNAL void printLog(const QString&);
    //void clearData();
};

#endif