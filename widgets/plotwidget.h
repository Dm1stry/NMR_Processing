#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QMap>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "dependencies/QCustomPlot/qcustomplot.h"

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
public slots:
    void updateData(QVector<double> x, QVector<double> y, int number = 0);
    void removeGraph(int number);
    void clear();
};

#endif