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
	this->plot_->graph(number)->setData(x, y);
}