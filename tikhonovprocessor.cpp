/*#include "tikhonovprocessor.h"
#include <Eigen/Dense>

TikhonovProcessor::TikhonovProcessor(QObject * parent /*= nullptr*//*)*/
/*  : BaseProcessor(parent)
{
    //temoporary set up

	alpha_ = 200;
	iterations_ = 100;
	T_min_ = 100;
	T_max_ = 1e7;
	p_size_ = 1000;

	
	//Eigen::setNbThreads(10);
	//Eigen::initParallel();
}

void TikhonovProcessor::Process()
{
	using namespace Eigen;
	
	emit processingStarted();
	emit processingStateUpdate(1);
  //--------Creating of a logspace---------------
    p_.reserve(this->p_size_ + 1);
    double p_min = -log10(this->T_max_);
    double p_max = -log10(this->T_min_);
    double p_step = (p_max - p_min) / (this->p_size_ - 1);
    for(size_t i = 0; i < this->p_size_; ++i)
    {
    	p_.push_back(pow(10, p_min));
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

	emit processingStateUpdate(2);

	MatrixXd K_t = K.transpose();

	MatrixXd W = (K_t * K + MatrixXd::Identity(this->p_size_, this->p_size_) * this->alpha_).inverse();

	emit processingStateUpdate(3);

	QVector<double> s_arr = A_;

	Map<VectorXd> s(s_arr.data(), s_arr.size());

	MatrixXd W_K_t_s = W * (K_t * s);

	emit processingStateUpdate(4);

	MatrixXd W_alpha = W * this->alpha_;

	VectorXd r = VectorXd::Zero(this->p_size_);

	emit processingStateUpdate(5);

	const uint step_to_update = iterations_ / 10;
	uint current_update_iteration = step_to_update;
	uint current_state = 0;

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
		if(iteration == current_update_iteration)
		{
			current_update_iteration += step_to_update;
			emit processingStateUpdate(current_state += 10);
		}
		//QCoreApplication::processEvents();
	}

	//--------------------------------------------------

	//--------------- Saving results -------------------

	VectorXd A = K * r;
	A_appr_ = QVector<double>(A.begin(), A.end());
	pt_.reserve(p_size_ + 1);
	for(auto p : p_)
	{
		pt_.push_back(1/p);
	}
	p_ = QVector<double>(r.begin(), r.end());

	NMRDataStruct processed_data {
		.A = this->A_appr_,
		.t = this->t_,
		.p = this->p_,
		.pt = this->pt_
	};

	emit processingDone(processed_data);
	//emit processingDone(this->convert_spectrum(processed_data));
	emit processingStateUpdate(0);

}  //void TikhonovProcessor::Process()

NMRDataStruct TikhonovProcessor::convert_spectrum(NMRDataStruct& processed_data)
{
	//----------- Get curve local maximums and minimums ----
	QVector<int> max_indexes;
	QVector<int> min_indexes;
	max_indexes.reserve(10);
	min_indexes.reserve(20);
	for(int i = 1; i < processed_data.p.size(); ++i)
	{
		if(processed_data.p[i - 1] < processed_data.p[i] && processed_data.p[i] > processed_data.p[i + 1])
		{
			max_indexes.push_back(i);
		}
		if((processed_data.p[i - 1] >= processed_data.p[i] && processed_data.p[i] < processed_data.p[i + 1]) || (processed_data.p[i - 1] > processed_data.p[i] && processed_data.p[i] <= processed_data.p[i + 1]))
		{
			min_indexes.push_back(i);
		}
	}
	//-----------------------------------------

	//---------- Get squares under peaks (components) ------
	//-----------------------------------------

	//---------- Change spectrum appearance ---
	//-----------------------------------------
	return processed_data;
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
*/