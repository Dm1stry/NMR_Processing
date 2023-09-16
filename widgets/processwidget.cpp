#include "processwidget.h"

ProcessWidget::ProcessWidget(PlotWidget * plot_widget, PlotWidget * spectrum_widget, QWidget * parent)
  : QTabWidget(parent)
{
    widgets_ << new TikhonovProcessWidget(plot_widget, spectrum_widget, this);
    for(auto widget : widgets_)
    {
        this->addTab((QWidget *)widget, widget->getName());
    }
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
}

void ProcessWidget::updateData(const QVector<double>& t, const QVector<double>&A)
{
	for(auto widget : widgets_)
	{
		widget->updateData(t, A);
	}
}