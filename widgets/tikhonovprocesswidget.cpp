#include "tikhonovprocesswidget.h"

TikhonovProcessWidget::TikhonovProcessWidget(QWidget * parent)
  : BaseProcessWidget("Тихонов", parent)
{
	this->setProcessor(new TikhonovProcessor(this));

	this->addParameter("T2min", "T<sub>2, min</sub>", 1e2);
	this->addParameter("T2max", "T<sub>2, max</sub>", 1e7);
	this->addParameter("alpha", "Параметр регуляризации", 200);
	this->addParameter("iterations", "Количество итераций", 1000);
	this->addParameter("p_size", "Дискретизация времени", 100);
    /*this->parameters_.insert(, new QLineEdit);
    this->parameters_.insert("T<sub>2, max</sub>", new QLineEdit);
    this->parameters_.insert("Параметр регуляризации", new QLineEdit);
    this->parameters_.insert("Количество итераций", new QLineEdit);
    this->parameters_.insert("Дискретизация времени", new QLineEdit);
	*/

    QVBoxLayout * widget_layout = new QVBoxLayout;
    QGridLayout * parameters_layout = this->getParametersLayout();
	QGridLayout * buttons_layout = this->getButtonsLayout();

    widget_layout->addLayout(parameters_layout);
    widget_layout->addLayout(buttons_layout);

    this->setLayout(widget_layout);

	//BaseProcessor * processor = getProcessor();
    //connect(this->process_button_, SIGNAL(clicked()), (TikhonovProcessor *)this->processor_, SLOT(Process()));
    //connect(this->processor_, SIGNAL(processingStateUpdate(const uchar&)), this->progress_bar_, SLOT(setValue(int)));
	
}