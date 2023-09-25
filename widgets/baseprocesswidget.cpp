#include "baseprocesswidget.h"

BaseProcessWidget::BaseProcessWidget(const QString& name, QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    name_(name),
    parameters_amount_(0),
    parameters_layout_(new QGridLayout),
    process_button_(new QPushButton("Обработать")),
    clear_data_button_(new QPushButton("Очистить данные")),
    clear_params_button_(new QPushButton("Сброс параметров")),
    progress_bar_(new QProgressBar),
    buttons_layout_(new QGridLayout),
    thread_(nullptr)
{
    this->progress_bar_->setRange(0, 100);
    this->progress_bar_->setOrientation(Qt::Orientation::Horizontal);

    this->buttons_layout_->addWidget(this->clear_params_button_, 0, 0, 1, 2);
    this->buttons_layout_->addWidget(this->clear_data_button_, 1, 0, 1, 2);
    this->buttons_layout_->addWidget(this->process_button_, 0, 3, 2, 1);
    this->buttons_layout_->addWidget(this->progress_bar_, 2, 0, 1, 4);

    this->process_button_->setEnabled(false);

    process_button_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    connect(this->clear_params_button_, SIGNAL(clicked()), this, SLOT(clearParams()));
    connect(this->clear_data_button_, SIGNAL(clicked()), SIGNAL(clearData()));
    
}

BaseProcessWidget::~BaseProcessWidget()
{
    if(this->thread_)
    {
        this->thread_->quit();
        this->thread_->wait();
    }
}

const QString& BaseProcessWidget::getName() const
{
    return this->name_;
}

BaseProcessor * BaseProcessWidget::getProcessor() const
{
    return this->processor_;
}

void BaseProcessWidget::setProcessor(BaseProcessor * processor)
{
    this->processor_ = processor;
    connect(this->process_button_, SIGNAL(clicked()), this->processor_, SLOT(Process()));
    connect(this->processor_, SIGNAL(processingStateUpdate(const uchar&)), this->progress_bar_, SLOT(setValue(int)));
}

void BaseProcessWidget::setProcessorInSeparateThread(BaseProcessor * processor)
{
    this->processor_ = processor;
    this->thread_ = new QThread(this);
    this->processor_->moveToThread(this->thread_);
    connect(this->process_button_, SIGNAL(clicked()), this->processor_, SLOT(Process()), Qt::QueuedConnection);
    connect(this->processor_, SIGNAL(processingStateUpdate(const int&)), this->progress_bar_, SLOT(setValue(int)), Qt::QueuedConnection);
    this->thread_->start(QThread::TimeCriticalPriority);
}

void BaseProcessWidget::addParameter(const QString& name, const QString& label, QVariant default_value, QValidator * validator)
{
    QLabel * parameter_label = new QLabel(label);
    this->parameters_labels_[name] = parameter_label;
    QLineEdit * parameter_edit = new QLineEdit();
    this->parameters_edits_[name] = parameter_edit;
    if(validator)
    {
        parameter_edit->setValidator(validator);
    }
    this->parameters_defaults_[name] = default_value;
    this->parameters_layout_->addWidget(parameter_label, parameters_amount_, 0);
    this->parameters_layout_->addWidget(parameter_edit, parameters_amount_++, 1);
    parameter_edit->setText(QString::number(default_value.toDouble()));
    connect(parameter_edit, SIGNAL(textChanged(const QString &text)), this->processor_, SLOT(
        [=](){
            QVariant value;
            bool convertable;
            value.setValue(parameter_edit->text().toDouble(&convertable));
            if(convertable)
                this->processor_->updateParameter(name, value);
        }
    ));
}

QGridLayout * BaseProcessWidget::getButtonsLayout() const
{
    return this->buttons_layout_;
}

QGridLayout * BaseProcessWidget::getParametersLayout() const
{
    return this->parameters_layout_;
}

void BaseProcessWidget::clearParams()
{
    for(auto parameter_name : this->parameters_edits_.keys())
    {
        this->parameters_edits_[parameter_name]->setText(parameters_defaults_[parameter_name].toString());
    }
}

/*virtual*/ void BaseProcessWidget::updateData(const NMRDataStruct& raw_data)
{
    this->processor_->updateData(raw_data);
    this->process_button_->setEnabled(true);  // A little bit incorrect, cause we need to check if parameters is set or not too
}

