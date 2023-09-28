#include "tikhonovprocessor.h"
#include <sys/types.h>
#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

TikhonovProcessor::TikhonovProcessor(QObject * parent /*= nullptr*/)
  : BaseProcessor(parent)
{
    //temoporary set up

	alpha_ = 200;
	iterations_ = 1000;
	T_min_ = 100;
	T_max_ = 1e8;
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
	uint t_size = this->t_.size();
	gsl_matrix * K = gsl_matrix_alloc(t_size, p_size_);
	/*
	for(uint p_index = 0; p_index < p_size_; ++p_index)
	{
		for(uint t_index = 0; t_index < t_size; ++t_index)
		{
			K->data[p_index * K->tda + t_index] = exp(-p_[p_index] * t_[t_index]);
		}
	}*/

	for(uint t_index = 0; t_index < t_size; ++t_index)
	{
		for(uint p_index = 0; p_index < p_size_; ++p_index)
		{
			K->data[t_index * K->tda + p_index] = exp(-p_[p_index] * t_[t_index]);
		}
	}

	emit processingStateUpdate(2);
	gsl_vector * s = gsl_vector_alloc(t_size);
	auto s_ptr = s->data;
	for(auto A_it = A_.begin(); A_it < A_.end(); A_it++, ++s_ptr)
	{
		*s_ptr = *A_it;
	}
	
	//W = (K_t * K + E{p_size_, p_size_} * alpha_)^(-1)
	gsl_matrix * W = gsl_matrix_alloc(p_size_, p_size_);
	gsl_matrix_set_identity(W);
	int status = gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1, K, K, this->alpha_, W);

	gsl_permutation * p = gsl_permutation_alloc(p_size_);
    int signum = 1;

	gsl_linalg_LU_decomp(W, p, &signum); // - нужно инвертировать W
	gsl_linalg_LU_invert(W, p, W);

	emit processingStateUpdate(4);

	//W_K_t_s = W * (K_t * s)
	gsl_vector * K_t_s = gsl_vector_alloc(p_size_);
	status = gsl_blas_dgemv(CblasTrans, 1, K, s, 0, K_t_s);

	gsl_vector * W_K_t_s = gsl_vector_alloc(p_size_);
	status = gsl_blas_dgemv(CblasNoTrans, 1, W, K_t_s, 0, W_K_t_s);

	gsl_vector * r = gsl_vector_calloc(p_size_);

	emit processingStateUpdate(5);
	
	const uint step_to_update = iterations_ / 10;
	uint current_update_iteration = step_to_update;
	uint current_state = 0;

	for(size_t iteration = 0; iteration < this->iterations_; ++iteration)
	{
		//r = W_K_t_s + W_alpha * r;
		gsl_blas_dgemv(CblasNoTrans, this->alpha_, W, r, 0, r);
		gsl_blas_daxpy(1, W_K_t_s, r);
		for(auto r_iterator = r->data; r_iterator < r->data + r->size; ++r_iterator)
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

	gsl_vector * A = gsl_vector_alloc(t_size);
	gsl_blas_dgemv(CblasNoTrans, 1, K, r, 0, A);
	A_appr_ = QVector<double>(A->data, A->data + A->size);
	pt_.reserve(p_size_ + 1);
	for(auto p : p_)
	{
		pt_.push_back(1/p);
	}
	p_ = QVector<double>(r->data, r->data + r->size);
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
	emit processingStateUpdate(0);
}  //void TikhonovProcessor::Process()

NMRDataStruct TikhonovProcessor::convert_spectrum(NMRDataStruct& processed_data)
{
    return processed_data;
}
