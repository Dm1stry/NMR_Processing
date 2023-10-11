#include "processwidget.h"

ProcessWidget::ProcessWidget(QWidget * parent)
  : QTabWidget(parent)
{
	this->addProcessWidget(new TikhonovProcessWidget(this));
	this->addProcessWidget(new SequentalProcessWidget(this));
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
}

void ProcessWidget::addProcessWidget(BaseProcessWidget * widget)
{
	widgets_ << widget;
	this->addTab((QWidget *)widget, widget->getName());
	connect(widget->getProcessor(), SIGNAL(processingDone(const NMRDataStruct&)), this, SIGNAL(processingDone(const NMRDataStruct&)));
	connect(widget, SIGNAL(clearData()), SIGNAL(clearData()));
	connect(widget->getProcessor(), SIGNAL(componentsFound(const NMRDataStruct&)), SIGNAL(componentsFound(const NMRDataStruct&)));
}

void ProcessWidget::updateData(const NMRDataStruct& raw_data)
{
	for(auto widget : widgets_)
	{
		widget->updateData(raw_data);
	}
}