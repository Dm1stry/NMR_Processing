#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QMap>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "dependencies/QCustomPlot/qcustomplot.h"

#include "nmrdatastruct.h"

class PlotWidget : public QWidget
{
Q_OBJECT
public:

    PlotWidget(QWidget * parent = nullptr);

private:
    QCustomPlot * plot_;
    QLabel * x_label_;
    QLabel * y_label_;
    QComboBox * x_box_;
    QComboBox * y_box_;

    QMap<int, int> graph_numbers_;
    const QVector<QPair<QString, QCPAxis::ScaleType>> scale_types_;

    inline void connections();
    inline void layoutSetup();

public slots:
    void updateData(QVector<double> x, QVector<double> y, int number = 0);
    void updateAsPlot(const NMRDataStruct& nmr_data, int number = 0);
    void updateAsSpectrum(const NMRDataStruct& nmr_data, int number = 0);
    void removeGraph(int number);
    void clear();

private slots:
    void rescaleXAxis(int scale_type);
    void rescaleYAxis(int scale_type);
    void rescaleAxis(int scale_type, bool x_axis = true);
};

#endif