#include "tikhonovprocessor.h"
#include <armadillo>
#include <cblas.h>

#include <QDebug>

TikhonovProcessor::TikhonovProcessor(QObject * parent /*= nullptr*/)
  : BaseProcessor(parent),
	alpha_(200),
	iterations_(1000),
	T_min_(100),
	T_max_(1e9),
	p_size_(1000),
	memory_(new double[p_size_ * 10000]),
	first_free_cell_(memory_),
	memory_size_(p_size_ * 10000)
{
	openblas_set_num_threads(8);
}

TikhonovProcessor::~TikhonovProcessor()
{
	delete[] this->memory_;
	this->memory_ = nullptr;
}

void TikhonovProcessor::updateParameter(QString parameter_name, QVariant parameter_value)
{
	if(parameter_name == "alpha")
	{
	this->alpha_ = parameter_value.toDouble();
	qDebug() << "alpha: " << alpha_;
	}
	else if(parameter_name == "iterations")
	{
	this->iterations_ = parameter_value.toUInt();
	qDebug() << "iterations: " << iterations_;
	}
	else if(parameter_name == "T2min")
	{
	this->T_min_ = parameter_value.toDouble();
	qDebug() << "Tmin: " << T_min_;
	}
	else if(parameter_name == "T2max")
	{
	this->T_max_ = parameter_value.toDouble();
	qDebug() << "Tmax: " << T_max_;
	}
	else if(parameter_name == "p_size")
	{
	this->p_size_ = parameter_value.toUInt();
	qDebug() << "p: " << p_size_;
	enlargeMemory(this->p_size_, this->A_.size());
	}
}

void TikhonovProcessor::updateData(const NMRDataStruct& raw_data)
{
	this->t_ = raw_data.t;
	this->A_ = raw_data.A;
	enlargeMemory(this->p_size_, this->A_.size());
}

void TikhonovProcessor::Process()
{
	emit processingStarted();
	emit processingStateUpdate(1);
  //--------Creating of a logspace---------------
	p_.clear();
	int capacity_needed = this->p_size_ + 1 - p_.capacity();
	if(capacity_needed > 0)
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
	uint t_size = this->t_.size();
	enlargeMemory(this->p_size_, t_size);

	arma::mat K(getMemory(t_size * p_size_), t_size, p_size_, false, true);

	for(uint t_index = 0; t_index < t_size; ++t_index)
	{
		for(uint p_index = 0; p_index < p_size_; ++p_index)
		{
			K(t_index, p_index) = exp(-p_[p_index] * t_[t_index]);
		}
	}

	emit processingStateUpdate(2);
	//gsl_vector * s = gsl_vector_alloc(t_size);
	arma::colvec s(A_.data(), t_size, false, true);
	
	double * K_t_ptr = getMemory(p_size_ * t_size);
	arma::mat K_t(K_t_ptr, p_size_, t_size, false, true);
	K_t = K.t();
	//W = (K_t * K + E{p_size_, p_size_} * alpha_)^(-1)
	
	arma::mat W(getMemory(p_size_ * p_size_), p_size_, p_size_, false, true);

	W = W.eye() * this->alpha_;
	W += K_t * K;
	W = inv(W);  //Спорно

	emit processingStateUpdate(4);

	//W_K_t_s = W * (K_t * s)
	arma::colvec W_K_t_s(K_t_ptr, p_size_, false, true);
	W_K_t_s = K_t * s;  //Спорно
	W_K_t_s = W * W_K_t_s;

	W *= this->alpha_;
	
	arma::colvec r(getMemory(p_size_), p_size_, false, true);
	r.zeros();

	emit processingStateUpdate(5);
	
	const uint step_to_update = iterations_ / 10;
	uint current_update_iteration = step_to_update;
	uint current_state = 0;

	for(size_t iteration = 0; iteration < this->iterations_; ++iteration)
	{
		//r = W_K_t_s + W_alpha * r;
		r = W_K_t_s + W * r;
		//r += W;
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
	}

	arma::vec A(K_t_ptr, t_size, false, true);
	A = K * r;
	A_appr_ = QVector<double>(A.begin(), A.end());
	pt_.clear();
	if(capacity_needed > 0)
		pt_.reserve(this->p_size_ + 1);
	for(auto p : p_)
	{
		pt_.push_back(1/p);
	}
	p_ = QVector<double>(r.begin(), r.end());
	p_max = *std::max_element(p_.begin(), p_.end());
	for(auto& p_i : p_)
	{
		p_i = p_i / p_max;
	}

	NMRDataStruct processed_data {
		.A = this->A_appr_,
		.t = this->t_,
		.p = this->p_,
		.pt = this->pt_
	};

	//emit processingDone(processed_data);
	emit processingDone(this->convert_spectrum(processed_data));
	this->getComponents(processed_data);
	emit processingStateUpdate(0);

	clearMemory();
	
}  //void TikhonovProcessor::Process()

void TikhonovProcessor::getComponents(const NMRDataStruct& processed_data)
{
	double full_S = abs(trapz_intergal(pt_.begin(), pt_.end(), p_.begin(), p_.end()));
	std::vector<size_t> peaks = argmax(p_.begin(), p_.end()); //error is here
	std::vector<size_t> minimums = argmineq(p_.begin(), p_.end());
	QVector<double> M;
	QVector<double> T;
	for(auto peak : peaks)
	{
		double peak_S = find_peak_S(peak, minimums);
		M.push_back(peak_S / full_S);
		T.push_back(this->pt_[peak]);
		/*if(peak_S > 0.005)
		{
			//M.push_back(peak_S / full_S);
			//T.push_back(this->pt_[peak]);
		}*/
	}

	NMRDataStruct components{
		.A = M,
		.t = T
	};

	getNoise(components);

	emit componentsFound(components);
}

inline double TikhonovProcessor::find_peak_S(const size_t& peak_index, std::vector<size_t> minimums)
{
	auto current_iter_up = find_nearest_greater(peak_index, minimums.begin(), minimums.end());
	size_t current_index_up = this->p_.length() - 1;
	if(current_iter_up != minimums.end())
		current_index_up = *current_iter_up;

	auto current_iter_down = find_nearest_less(peak_index, minimums.begin(), minimums.end());
	size_t current_index_down = 0;
	if(current_iter_down != minimums.end())
		current_index_down = *current_iter_down;


	return abs(trapz_intergal(
		this->pt_.begin() + current_index_down, 
		this->pt_.begin() + current_index_up + 1,
		this->p_.begin() + current_index_down, 
		this->p_.begin() + current_index_up + 1
	));
}

void TikhonovProcessor::getNoise(NMRDataStruct& components)
{
	/*QVector<double> approximated_A;
	approximated_A.resize(t_.size());
	approximated_A.fill(0);
	for(int i = 0; i < components.A.size(); ++i)
	{
		for(int j = 0; j < approximated_A.size(); ++j)
		{
			approximated_A[j] += components.A[i] * exp(-this->t_[j] / components.t[i]);
		}
	}

	for(int j = 0; j < this->A_.size(); ++j)
	{
		approximated_A[j] -= this->A_[j];
	}

	components.p = approximated_A;*/
	for(int j = 0; j < this->A_.size(); ++j)
	{
		this->A_[j] -= this->A_appr_[j];
	}

	components.p = this->A_;
	components.pt = this->t_;
}

NMRDataStruct TikhonovProcessor::convert_spectrum(NMRDataStruct& processed_data)
{
    return processed_data;
}

void TikhonovProcessor::enlargeMemory(const uint& p_size, const uint& t_size)
{
	if(p_size * (2 * t_size + p_size + 1) > this->memory_size_)
	{
		this->memory_size_ = p_size * (2 * t_size + p_size + 1);
		delete[] this->memory_;
		this->memory_ = new double[this->memory_size_ + 1];
		this->first_free_cell_ = this->memory_;
	}
}

double * TikhonovProcessor::getMemory(const size_t& size)
{
	double * returnable = this->first_free_cell_;
	this->first_free_cell_ += size;
	return returnable;
}

void TikhonovProcessor::clearMemory()
{
	first_free_cell_ = memory_;
}