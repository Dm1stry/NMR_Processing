#include "tikhonovprocesswidget.h"

TikhonovProcessWidget::TikhonovProcessWidget(QWidget * parent)
  : BaseProcessWidget(parent)
{
    labels_ << *(new QLabel("T<sub>2, min</sub>")) << *(new QLabel("T<sub>2, max</sub>"));
}