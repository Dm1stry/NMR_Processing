#ifndef TIKHONOVPROCESSWIDGET_H
#define TIKHONOVPROCESSWIDGET_H

#include <QFormLayout>
#include <QVBoxLayout>

#include "baseprocesswidget.h"
#include "tikhonovprocessor.h"
#include "plotwidget.h"

class TikhonovProcessWidget : public BaseProcessWidget
{
Q_OBJECT
public:
    TikhonovProcessWidget(PlotWidget * plot, PlotWidget * spectrum, QWidget * parent = nullptr);
private:
public slots:
    virtual void clearParams();
};

#endif