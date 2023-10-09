#include "sequentalprocesswidget.h"

SequentalProcessWidget::SequentalProcessWidget(QWidget * parent)
  : BaseProcessWidget("Посл. аппроксимация", parent)
{
    BaseProcessor * processor = new SequentalProcessor();
    
}