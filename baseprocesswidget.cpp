#include "baseprocesswidget.h"

BaseProcessWidget::BaseProcessWidget(QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    process_button_(new QPushButton("Обработать")),
    clear_data_button_(new QPushButton("Очистить данные")),
    clear_params_button_(new QPushButton("Сброс параметров")),
    buttons_layout_(new QGridLayout)
{
    this->buttons_layout_->addWidget(this->clear_params_button_, 0, 0, 1, 2);
    this->buttons_layout_->addWidget(this->clear_data_button_, 1, 0, 1, 2);
    this->buttons_layout_->addWidget(this->process_button_, 0, 3, 2, 1);
}