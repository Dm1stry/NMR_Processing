#include "processwidget.h"

ProcessWidget::ProcessWidget(QWidget * parent)
  : QTabWidget(parent)
{
    widgets_ << new TikhonovProcessWidget(this);
    for(auto widget : widgets_)
    {
        this->addTab((QWidget *)widget, widget->getName());
    }
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
}