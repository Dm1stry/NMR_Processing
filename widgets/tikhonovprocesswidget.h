#ifndef TIKHONOVPROCESSWIDGET_H
#define TIKHONOVPROCESSWIDGET_H

#include <QFormLayout>
#include <QVBoxLayout>

#include "baseprocesswidget.h"
#include "tikhonovprocessor.h"

class TikhonovProcessWidget : public BaseProcessWidget
{
Q_OBJECT
public:
    TikhonovProcessWidget(QWidget * parent = nullptr);
public slots:
    virtual void clearParams();
};

#endif