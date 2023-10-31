#include "sequentalprocesswidget.h"

SequentalProcessWidget::SequentalProcessWidget(QWidget * parent)
  : BaseProcessWidget("Посл. аппроксимация", parent)
{
    BaseProcessor * processor = new SequentalProcessor();
    this->setProcessorInSeparateThread(processor);

	this->addParameter("N_max", "N<sub>max</sub>", 5);
  this->addParameter("T_max", "T<sub>max</sub>", 1e9);
  this->addParameter("T_min", "T<sub>min</sub>", 1e-2);

	QVBoxLayout * widget_layout = new QVBoxLayout;
	QGridLayout * parameters_layout = this->getParametersLayout();
	QGridLayout * buttons_layout = this->getButtonsLayout();

	widget_layout->addLayout(parameters_layout);
    widget_layout->addLayout(buttons_layout);

    this->setLayout(widget_layout);
}