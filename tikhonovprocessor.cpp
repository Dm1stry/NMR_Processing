#include "tikhonovprocessor.h"

TikhonovProcessor::TikhonovProcessor(QObject * parent /*= nullptr*/)
  : BaseProcessor(parent)
{
    
}

void TikhonovProcessor::Process()
{
    
}

void TikhonovProcessor::setParameter(QPair<QString, double> parameter)
{
  if(parameter.first == "Alpha")
  {
    this->alpha_ = parameter.second;
  }
  if(parameter.first == "Iterations")
  {
    this->iterations_ = parameter.second;
  }
  if(parameter.first == "T_min")
  {
    this->T_min_ = parameter.second;
  }
  if(parameter.first == "T_max")
  {
    this->T_max_ = parameter.second;
  }
  if(parameter.first == "p_size")
  {
    this->p_size_ = parameter.second;
  }
}