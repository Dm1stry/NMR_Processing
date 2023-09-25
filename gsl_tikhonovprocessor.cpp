//#include "tikhonovprocessor.h"
//#include <sys/types.h>
//#include <stdio.h>
/*#include <gsl/gsl_blas.h>

TikhonovProcessor::TikhonovProcessor(QObject * parent /*= nullptr*//*)*/
/*  : BaseProcessor(parent)
{
    //temoporary set up

	alpha_ = 200;
	iterations_ = 100;
	T_min_ = 100;
	T_max_ = 1e7;
	p_size_ = 1000;


}

void TikhonovProcessor::updateParameter(QString parameter_name, QVariant parameter_value)
{
	if(parameter_name == "Alpha")
	{
	this->alpha_ = parameter_value.toDouble();
	}
	else if(parameter_name == "Iterations")
	{
	this->iterations_ = parameter_value.toUInt();
	}
	else if(parameter_name == "T_min")
	{
	this->T_min_ = parameter_value.toDouble();
	}
	else if(parameter_name == "T_max")
	{
	this->T_max_ = parameter_value.toDouble();
	}
	else if(parameter_name == "p_size")
	{
	this->p_size_ = parameter_value.toUInt();
	}
}

void TikhonovProcessor::updateData(const NMRDataStruct& raw_data)
{
	this->t_ = raw_data.t;
	this->A_ = raw_data.A;
}

void TikhonovProcessor::Process()
{

}

NMRDataStruct TikhonovProcessor::convert_spectrum(NMRDataStruct& processed_data)
{
    return processed_data;
}
*/