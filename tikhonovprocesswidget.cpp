#include "tikhonovprocesswidget.h"

TikhonovProcessWidget::TikhonovProcessWidget(QWidget * parent)
  : BaseProcessWidget("Тихонов", parent)
{
    this->parameters_.insert("T<sub>2, min</sub>", new QLineEdit);
    this->parameters_.insert("T<sub>2, max</sub>", new QLineEdit);
    this->parameters_.insert("Параметр регуляризации", new QLineEdit);
    this->parameters_.insert("Количество итераций", new QLineEdit);
    this->parameters_.insert("Дискретизация времени", new QLineEdit);

    QVBoxLayout * widget_layout = new QVBoxLayout;
    QFormLayout * parameters_layout = new QFormLayout;

    for(auto parameter = parameters_.keyBegin(); parameter != parameters_.keyEnd(); ++parameter)
    {
        parameters_layout->addRow(*parameter, parameters_[*parameter]);
    }
    widget_layout->addLayout(parameters_layout);
    widget_layout->addLayout(this->buttons_layout_);

    this->setLayout(widget_layout);
}

/*virtual*/ void TikhonovProcessWidget::clearParams()
{

}

/*virtual*/ void TikhonovProcessWidget::Process()
{

}