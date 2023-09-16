#include "baseprocesswidget.h"

BaseProcessWidget::BaseProcessWidget(const QString& name, PlotWidget * plot_widget, PlotWidget * spectrum_widget,  QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    name_(name),
    process_button_(new QPushButton("Обработать")),
    clear_data_button_(new QPushButton("Очистить данные")),
    clear_params_button_(new QPushButton("Сброс параметров")),
    progress_bar_(new QProgressBar),
    buttons_layout_(new QGridLayout),
    plot_(plot_widget),
    spectrum_(spectrum_widget)
{
    this->progress_bar_->setRange(0, 10);
    this->progress_bar_->setOrientation(Qt::Orientation::Horizontal);

    this->buttons_layout_->addWidget(this->clear_params_button_, 0, 0, 1, 2);
    this->buttons_layout_->addWidget(this->clear_data_button_, 1, 0, 1, 2);
    this->buttons_layout_->addWidget(this->process_button_, 0, 3, 2, 1);
    this->buttons_layout_->addWidget(this->progress_bar_, 2, 0, 1, 4);

    this->process_button_->setEnabled(false);

    process_button_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    connect(this->clear_params_button_, &QPushButton::clicked, this, &BaseProcessWidget::clearParams);
    connect(this->clear_data_button_, SIGNAL(clicked()), SIGNAL(clearData()));
    //connect(this->process_button_, SIGNAL(clicked()), this->processor_, SLOT(Process()));
}

const QString& BaseProcessWidget::getName() const
{
    return name_;
}


/*virtual*/ void BaseProcessWidget::updateData(const QVector<double>& t, const QVector<double>& A)
{
    this->processor_->updateData(t, A);
    this->process_button_->setEnabled(true);
}