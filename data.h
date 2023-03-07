#ifndef DATA_H
#define DATA_H
#include <QPair>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <filesystem>

enum class ExperimentType
{
    empty,
    CPMG,
    T1ir,
    T2dfi
};

class Data
{
public:
    //Data(QVector<double> A, QVector<double> t);
    //Data(std::filesystem::path);
    Data();
    bool readAsCPMG(QString path);
    QVector<double> getAmplitudes() const;
    QVector<double> getTimes() const;
private:
    QVector<double> A_;
    QVector<double> t_;
    ExperimentType data_type_;
};

#endif // DATA_H
