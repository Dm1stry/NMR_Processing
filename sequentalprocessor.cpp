#include "sequentalprocessor.h"

SequentalProcessor::SequentalProcessor(QObject * parent)
  : BaseProcessor(parent)
{}

SequentalProcessor::~SequentalProcessor()
{}

void SequentalProcessor::updateParameter(QString parameter_name, QVariant parameter_value)
{
	if(parameter_name == "N_max")
	{
		this->N_max_ = parameter_value.toDouble();
	}
}

void SequentalProcessor::updateData(const NMRDataStruct& raw_data)
{
    this->t_ = raw_data.t;
	this->A_ = raw_data.A;
}

void SequentalProcessor::Process()
{
    
}