#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget * parent /*= nullptr*/)
  : QWidget(parent),
  	plot_(new CustomPlotZoom),
    x_label_(new QLabel("X:")),
    x_box_(new QComboBox),
    y_label_(new QLabel("Y:")),
    y_box_(new QComboBox),
	home_button_(new QPushButton),
	scale_types_({{"Линейно", QCPAxis::ScaleType::stLinear}, {"Логарифмически", QCPAxis::ScaleType::stLogarithmic}})
{
	this->plot_->setZoomMode(true);
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

	connect(this->home_button_, SIGNAL(clicked()), this, SLOT(homeView()));
}

inline void PlotWidget::layoutSetup()
{
	this->home_button_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	//this->home_button_->setIcon()

	QHBoxLayout * widget_layout = new QHBoxLayout;

	QVBoxLayout * plot_layout = new QVBoxLayout;
	QVBoxLayout * buttons_layout = new QVBoxLayout;

	plot_layout->addWidget(this->plot_);

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
	
	plot_layout->addLayout(scale_layout);  

	widget_layout->addLayout(plot_layout);

	buttons_layout->addWidget(this->home_button_);

	widget_layout->addLayout(buttons_layout);  

	this->setLayout(widget_layout);

	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void PlotWidget::updateData(QVector<double> x, QVector<double> y, int number)
{
	if(!this->plot_->graph(number))  // Потенциально возможна ошибка при попытке обновить график с большим номером, который не существует
	{
		this->graph_numbers_[number] = this->plot_->graphCount();
		this->plot_->addGraph();
		this->plot_->graph(this->graph_numbers_[number])->setPen(QPen(Qt::red));
	}
	this->plot_->graph(this->graph_numbers_[number])->setData(x, y);
	this->plot_->graph(this->graph_numbers_[number])->rescaleAxes();
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
	QComboBox * box;
	if(x_axis)
	{
		axis = this->plot_->xAxis;
		box = this->x_box_;
	}
	else
	{
		axis = this->plot_->yAxis;
		box = this->y_box_; 
	}

	axis->setScaleType(scale_types_[scale_type].second);

	if(scale_types_[scale_type].second == QCPAxis::ScaleType::stLogarithmic)
	{
		axis->setTicker(log_ticker);
		box->setCurrentIndex(1);
	}
	else
	{
		axis->setTicker(linear_ticker);
		box->setCurrentIndex(0);
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

void PlotWidget::homeView()
{
	this->plot_->rescaleAxes();
	this->plot_->replot();
}