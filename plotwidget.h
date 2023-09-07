#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "dependencies/QCustomPlot/qcustomplot.h"

class PlotWidget : public QWidget
{
Q_OBJECT

public:
    PlotWidget(QWidget * parent = nullptr);
};

#endif