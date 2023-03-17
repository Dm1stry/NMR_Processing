#ifndef DATA_H
#define DATA_H
#include <QPair>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <cmath>


enum class ExperimentType
{
    empty,
    CPMG,  //КПМГ
    T1ir,  //Инверсия-Восстановление
    T2dfi  //Спад Свободной Индукции
};

class Data
{
public:
    //Data(QVector<double> A, QVector<double> t);
    //Data(std::filesystem::path);
    Data();
    bool readAsCPMG(QString path);
    bool readFictiveData();
    QVector<double> getAmplitudes() const;
    QVector<double> getTimes() const;
private:
    QVector<double> A_;
    QVector<double> t_;
    ExperimentType data_type_;
};

#endif // DATA_H
