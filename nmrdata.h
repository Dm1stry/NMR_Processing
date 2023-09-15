#ifndef NMRDATA_H
#define NMRDATA_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

#include <QRegExp>


class NMRData : public QObject
{
Q_OBJECT
public:
    NMRData(QObject * parent = nullptr);
private:
    QVector<double> A_;
    QVector<double> t_;
public slots:
    void readAsCPMG(const QString& filepath);
    void setData(QVector<double> A, QVector<double> t);
signals:
    void wrongData();
    void dataUpdated(const QVector<double>&, const QVector<double>&);
};

#endif