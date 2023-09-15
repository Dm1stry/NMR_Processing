#include "tikhonovprocessor.h"

TikhonovProcessor::TikhonovProcessor(QObject * parent /*= nullptr*/)
  : BaseProcessor(parent)
{
    
}

void TikhonovProcessor::Process()
{
	using namespace Eigen; 
  //--------Creating of a logspace---------------
    p_.reserve(this->p_size_);
    double p_min = -log10(this->T_max_);
    double p_max = -log10(this->T_min_);
    double p_step = (p_max - p_min) / (this->p_size_ - 1);
    for(size_t i = 0; i < this->p_size_; ++i)
    {
    	p_.push_back(p_min);
    	p_min += p_step;
    }
  //---------------------------------------------

  //-------------- Regularization ---------------
	uint t_size = this->t_.size();
	MatrixXd K(p_size_, t_size);
	for(uint p_index = 0; p_index < p_size_; ++p_index)
	{
		for(uint t_index = 0; t_index < t_size; ++t_index)
		{
			K(p_index, t_index) = exp(-p_[p_index] * t_[t_index]);
		}
	}

	MatrixXd K_t = K.transpose();

	MatrixXd W = (K_t * K + MatrixXd::Identity(this->p_size_, this->p_size_) * this->alpha_).inverse();

	QVector<double> s_arr = A_;

	Map<VectorXd> s(s_arr.data(), s_arr.size());

	MatrixXd W_K_t_s = W * (K_t * s);

	MatrixXd W_alpha = W * this->alpha_;

	VectorXd r = VectorXd::Zero(this->p_size_);

	for(size_t iteration = 0; iteration < this->iterations_; ++iteration)
	{
		r = W_K_t_s + W_alpha * r;
		for(auto r_iterator = r.begin(); r_iterator < r.end(); ++r_iterator)
		{
			if(*r_iterator < 0)
			{
				*r_iterator = 0;
			}
		}
	}

	//--------------------------------------------------

	//--------------- Saving results -------------------

	VectorXd A = K * r;
	A_appr_ = QVector<double>(A.begin(), A.end());
	pt_.reserve(p_size_);
	for(auto p : p_)
	{
		pt_.push_back(1/p);
	}
	p_ = QVector<double>(r.begin(), r.end());

	emit processingDone();
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

void TikhonovProcessor::updateData(QVector<double> t, QVector<double> A)
{
  this->t_ = t;
  this->A_ = A;
}