#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include <QTabWidget>

#include "tikhonovprocesswidget.h"


class ProcessWidget : public QTabWidget
{
Q_OBJECT
public:
    ProcessWidget(PlotWidget * plot_widget, PlotWidget * spectrum_widget, QWidget * patent = nullptr);
private:
    QVector<BaseProcessWidget *> widgets_;
public slots:
    void updateData(const QVector<double>& t, const QVector<double>& A);
};

#endif