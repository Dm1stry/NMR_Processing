#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    plot_(new QCustomPlot),
    x_label_(new QLabel("X:")),
    x_box_(new QComboBox),
    y_label_(new QLabel("Y:")),
    y_box_(new QComboBox)
{

	this->plot_->addGraph();
	graph_numbers_[0] = 0;
	QVBoxLayout * widget_layout = new QVBoxLayout;

	widget_layout->addWidget(this->plot_);

	QHBoxLayout * scale_layout = new QHBoxLayout;

	scale_layout->addWidget(this->y_label_);
	scale_layout->addWidget(this->y_box_);
	scale_layout->addWidget(this->x_label_);
	scale_layout->addWidget(this->x_box_);

	widget_layout->addLayout(scale_layout);    

	this->setLayout(widget_layout);

	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void PlotWidget::updateData(QVector<double> x, QVector<double> y, int number)
{
	if(!this->plot_->graph(number))  // Потенциально возможна ошибка при попытке обновить график с большим номером, который не существует
	{
		this->graph_numbers_[number] = this->plot_->graphCount();
		this->plot_->addGraph();
	}
	this->plot_->graph(this->graph_numbers_[number])->setData(x, y);
	this->plot_->xAxis->setRange(0, x.last());
	this->plot_->yAxis->setRange(0, *(std::max_element(y.begin(), y.end())));
	this->plot_->replot();
}

void PlotWidget::updateAsPlot(const NMRDataStruct& nmr_data, int number)
{
	this->updateData(nmr_data.t, nmr_data.A, number);
}

void PlotWidget::updateAsSpectrum(const NMRDataStruct& nmr_data, int number)
{
	this->updateData(nmr_data.pt, nmr_data.p, number);
}

void PlotWidget::removeGraph(int number)
{
	this->plot_->removeGraph(this->graph_numbers_[number]);
	this->graph_numbers_.remove(number);
}

void PlotWidget::clear()
{
	this->plot_->clearGraphs();
	this->graph_numbers_.clear();
}