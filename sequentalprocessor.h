#ifndef SEQUENTALPROCESSOR_H
#define SEQUENTALPROCESSOR_H

#include "baseprocessor.h"
#include "approximation.h"
#include "mathfunctions.h"
#include <vector>
#include <span>
#include <omp.h>

/*
* Ход обработки:
* 1) Получение данных (updateData)
* 2) Задание параметров (updateParameter)
* 3) Вычисление мощности шума ()
* 3.1) Разбиение исходной кривой на отрезки (возможно перекрывающиеся, но пока нет)
* 3.2) Аппроксимация каждого из таких отрезков полиномом
* 3.2.1) Если отрезки перекрываются, усреднение значений в перекрывающихся областях
* 3.3) Вычитание получившейся гладкой кривой из исходных данных
* 3.4) Вычисление среднеквадратичного отклонения для получившейся шумовой кривой *
* 4) Цикл подбора количества экспонент
* 4.1) Аппроксимация исходных данных n-ным количеством экспонент
* 4.2) Вычитание аппроксимационной кривой из исходных данных
* 4.3) Разбиение разности на отрезки
* 4.4) Если среднеквадратичное отклонение на всех участках порядка уровня шума,
* значит количество экспонент, которыми мы аппроксимируем достаточно и можно вернуть результат
*/

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

    //QVector<double> diff_;

    uint N_max_;
    double T_min_;
    double T_max_;

    void createSpectrum(NMRDataStruct& processed_data);
    void getNoise(NMRDataStruct& components);
    double getNoiseLevel();
    bool approximationIsGoodEnough(const appr_funcs::approximation_data& data, const double noise_level);

};

#endif