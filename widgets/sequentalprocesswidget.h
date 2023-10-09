#ifndef SEQUENTALPROCESSWIDGET_H
#define SEQUENTALPROCESSWIDGET_H

#include "baseprocesswidget.h"
#include "sequentalprocessor.h"

class SequentalProcessWidget : public BaseProcessWidget
{
Q_OBJECT
public:
    SequentalProcessWidget(QWidget * parent = nullptr);
};

#endif