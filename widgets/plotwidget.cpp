#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    plot_(new QCustomPlot),
    x_label_(new QLabel("X:")),
    x_box_(new QComboBox),
    y_label_(new QLabel("Y:")),
    y_box_(new QComboBox),
	scale_types_({{"Линейно", QCPAxis::ScaleType::stLinear}, {"Логарифмически", QCPAxis::ScaleType::stLogarithmic}})
{

	this->plot_->addGraph();
	graph_numbers_[0] = 0;
	this->plot_->graph(0)->rescaleAxes(true);
	this->plot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	
	layoutSetup();
	connections();
}

inline void PlotWidget::connections()
{
	connect(this->x_box_, SIGNAL(activated(int)), this, SLOT(rescaleXAxis(int)));
	connect(this->y_box_, SIGNAL(activated(int)), this, SLOT(rescaleYAxis(int)));
}

inline void PlotWidget::layoutSetup()
{
	QVBoxLayout * widget_layout = new QVBoxLayout;

	widget_layout->addWidget(this->plot_);

	QHBoxLayout * scale_layout = new QHBoxLayout;
	
	for(auto scale_type_ : scale_types_)
	{
		this->x_box_->addItem(scale_type_.first);
		this->y_box_->addItem(scale_type_.first);
	}

	scale_layout->addWidget(this->x_label_);
	scale_layout->addWidget(this->x_box_);
	scale_layout->addWidget(this->y_label_);
	scale_layout->addWidget(this->y_box_);
	

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
	this->plot_->graph(this->graph_numbers_[number])->rescaleAxes(true);
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
	this->plot_->replot();
}

void PlotWidget::clear()
{
	this->plot_->clearGraphs();
	this->graph_numbers_.clear();
	this->plot_->replot();
}

void PlotWidget::rescaleAxis(int scale_type, bool x_axis)
{
	static QSharedPointer<QCPAxisTickerLog> log_ticker(new QCPAxisTickerLog);
	static QSharedPointer<QCPAxisTickerFixed> linear_ticker(new QCPAxisTickerFixed);
	QCPAxis * axis;
	if(x_axis)
	{
		axis = this->plot_->xAxis;
	}
	else
	{
		axis = this->plot_->yAxis;
	}

	axis->setScaleType(scale_types_[scale_type].second);

	if(scale_types_[scale_type].second == QCPAxis::ScaleType::stLogarithmic)
	{
		axis->setTicker(log_ticker);
	}
	else
	{
		axis->setTicker(linear_ticker);
	}
	axis->setNumberFormat("eb");
	axis->setNumberPrecision(0);

	this->plot_->replot();
}

void PlotWidget::rescaleXAxis(int scale_type)
{
	this->rescaleAxis(scale_type, true);
}

void PlotWidget::rescaleYAxis(int scale_type)
{
	this->rescaleAxis(scale_type, false);
}