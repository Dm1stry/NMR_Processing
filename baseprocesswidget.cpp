#include "baseprocesswidget.h"

BaseProcessWidget::BaseProcessWidget(const QString& name, QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    name_(name),
    process_button_(new QPushButton("Обработать")),
    clear_data_button_(new QPushButton("Очистить данные")),
    clear_params_button_(new QPushButton("Сброс параметров")),
    buttons_layout_(new QGridLayout)
{
    this->buttons_layout_->addWidget(this->clear_params_button_, 0, 0, 1, 2);
    this->buttons_layout_->addWidget(this->clear_data_button_, 1, 0, 1, 2);
    this->buttons_layout_->addWidget(this->process_button_, 0, 3, 2, 1);

    //this->process_button_->setEnabled(false);

    process_button_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    connect(this->clear_params_button_, &QPushButton::clicked, this, &BaseProcessWidget::clearParams);
    connect(this->clear_data_button_, SIGNAL(clicked()), SIGNAL(clearData()));
    //connect(this->process_button_, SIGNAL(clicked()), this->processor_, SLOT(Process()));
}

const QString& BaseProcessWidget::getName() const
{
    return name_;
}

