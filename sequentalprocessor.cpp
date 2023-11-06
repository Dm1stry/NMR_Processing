#include "sequentalprocessor.h"
#pragma warning(push)
#pragma warning(disable : 4267)
#pragma warning(disable : 4996)

SequentalProcessor::SequentalProcessor(QObject * parent)
  : BaseProcessor(parent), N_max_(5), T_max_(1e9), T_min_(1e-2)
{
	omp_set_num_threads(8);
}

SequentalProcessor::~SequentalProcessor()
{}

void SequentalProcessor::updateParameter(QString parameter_name, QVariant parameter_value)
{
	if(parameter_name == "N_max")
	{
		this->N_max_ = parameter_value.toDouble();
	}
	if(parameter_name == "T_max")
	{
		this->T_max_ = parameter_value.toDouble();
	}
	if(parameter_name == "T_min")
	{
		this->T_min_ = parameter_value.toDouble();
	}
}

void SequentalProcessor::updateData(const NMRDataStruct& raw_data)
{
    this->t_ = raw_data.t;
	this->A_ = raw_data.A;
}

void SequentalProcessor::Process()
{
	std::vector<double> upper_bounds;
	std::vector<double> lower_bounds;
	params_.reserve(N_max_ * 2 + 1);  //Вектор хранящий параметры затухания, {A1, T1, A2, T2, ..., An, Tn}
	upper_bounds.reserve(N_max_ * 2 + 1);  //Максимально возможные значения параметров, {1, T_max, 1, T_max, 1, T_max, ...}
	lower_bounds.reserve(N_max_ * 2 + 1);  //Минимально возможные значения параметров, {0.01, T_min, 0.01, T_min, ...}

	appr_funcs::approximation_data data{
			.x_src = this->t_.toStdVector(),
			.y_src = this->A_.toStdVector()
	};

	const double average_time = (T_max_ + T_min_) / 2;
	const double min_ratio = 0.01;

	std::vector<double> prev_params;
    for(uint i = 1; i <= N_max_; ++i)
	{
		double params_ratio = 1.0 / i;
		params_.clear();
		params_.resize(2 * i);
		lower_bounds.clear();
		lower_bounds.resize(2 * i);
		upper_bounds.clear();
		upper_bounds.resize(2 * i);
		for(uint n = 0; n < 2 * i; n+= 2)
		{
			lower_bounds[n] = min_ratio;
			lower_bounds[n + 1] = T_min_;
			upper_bounds[n] = 1;
			upper_bounds[n + 1] = T_max_;
			params_[n] = params_ratio;
			params_[n + 1] = average_time;
		}

		prev_params = params_;
		params_ = appr_funcs::approximate_exp_n(data, lower_bounds, upper_bounds, params_);

		if(approximationIsGoodEnough(prev_params, data))
		{
			break;
		}
	}

	A_appr_ = QVector<double>::fromStdVector(appr_funcs::exp_n(data.x_src, params_));

	NMRDataStruct processed_data {
		.A = A_appr_,
		.t = t_,
	};

	createSpectrum(processed_data);

	NMRDataStruct components;

	for(int i = 0; i < params_.size(); i += 2)
	{
		components.A.push_back(params_[i]);
		components.t.push_back(params_[i + 1]);
	}

	getNoise(components);

	emit componentsFound(components);
	emit processingDone(processed_data);
}

double SequentalProcessor::getNoiseLevel()
{
	const uint piece_len = 100;  // Количество точек в отрезке разбиения
	std::vector<double> noise_A(A_.begin(), A_.end());
	std::vector<double> sub_vector_A;  //Отрезок разбиения содержащий амплитуды
	std::vector<double> sub_vector_t;  //Отрезок разбиения, содержащий время
	sub_vector_A.reserve(piece_len + 2);
	sub_vector_t.reserve(piece_len + 2);
	uint current_point = 0;  //Точка, являющаяся отрезком разбиения
	std::vector<double> params = {0, 0, 0, 0, 0};  // Параметры полиномиальной аппроксимации
	while(current_point < A_.size())
	{
		sub_vector_A.clear();
		sub_vector_t.clear();
		auto sub_A_begin_it = noise_A.begin() + current_point;  // Итераторы на начало и конец отрезка рабиения в скопированных исходных данных
		auto sub_t_begin_it = t_.begin() + current_point;
		auto sub_A_end_it = sub_A_begin_it + piece_len;
		auto sub_t_end_it = sub_t_begin_it + piece_len;
		if(current_point + piece_len >= noise_A.size())  // Для последнего отрезка за конец принимается конец вектора исходных данных
		{
			sub_A_end_it = noise_A.end();
			sub_t_end_it = t_.end();
		}

		sub_vector_A.assign(sub_A_begin_it, sub_A_end_it);  // Копирование участка данных в стд вектор (можно сделать на указателях и без копирования, но пока пусть будет так)
		sub_vector_t.assign(sub_t_begin_it, sub_t_end_it);

		params = appr_funcs::approximate_pol_n(sub_vector_t, sub_vector_A, params);  // Полиномиальная аппроксимация
		std::vector<double> apprximated_curve = appr_funcs::polynom(sub_vector_t, params);  // Получение полиномиальной кривой
		auto approximated_curve_it = apprximated_curve.begin();
		for(auto it = sub_A_begin_it; it < sub_A_end_it; ++it, ++approximated_curve_it)  // Вычитание полученной кривой из исходных данных
		{
			*it -= *approximated_curve_it;
			*it = (*it) * (*it);
		}
		current_point += piece_len;  // Смещение точки начала отрезка на длину отрезка
	}//while(current_point < A_.size())
	double noise = trapz_intergal(t_.begin(), t_.end(), noise_A.begin(), noise_A.end());
	return noise / (*(t_.end() - 1) - *(t_.begin()));
}

bool SequentalProcessor::approximationIsGoodEnough(const std::vector<double>& prev, const appr_funcs::approximation_data& data)
{
	if(prev.empty())
	{
		return false;
	}
	std::vector<double> sq_diff_prev(data.x_src.size());
	std::vector<double> sq_diff_curr(data.x_src.size());
	std::vector<double> prev_exp = appr_funcs::exp_n(data.x_src, prev);
	std::vector<double> curr_exp = appr_funcs::exp_n(data.x_src, params_);
	#pragma omp parallel for
	for(int i = 0; i < prev_exp.size(); ++i)
	{
		double tmp_prev = prev_exp[i] - data.y_src[i];
		double tmp_curr = curr_exp[i] - data.y_src[i];
		sq_diff_prev[i] = tmp_prev * tmp_prev / data.x_src[i];
		sq_diff_curr[i] = tmp_curr * tmp_curr / data.x_src[i];
	}
	double curr_integral = trapz_intergal(data.x_src, sq_diff_curr);
	double prev_integral = trapz_intergal(data.x_src, sq_diff_prev);

	return get_power(curr_integral) == get_power(prev_integral);

	//Среднеквадратичное напряжение шума
}

void SequentalProcessor::createSpectrum(NMRDataStruct& processed_data)
{
	p_.reserve(3 * params_.size() + 2);
	pt_.reserve(3 * params_.size() + 2);
	p_.push_back(0);
	pt_.push_back(T_min_);
	for(int i = 0; i < params_.size(); i+=2)
	{
		p_.push_back(0);
		pt_.push_back(params_[i + 1] * 0.99999);
		p_.push_back(params_[i]);
		pt_.push_back(params_[i + 1]);
		p_.push_back(0);
		pt_.push_back(params_[i + 1] * 1.00001);
	}
	p_.push_back(0);
	pt_.push_back(T_max_);
	processed_data.pt = pt_;
	processed_data.p = p_;
}

void SequentalProcessor::getNoise(NMRDataStruct& components)
{
	#pragma omp parallel for
	for(int j = 0; j < this->A_.size(); ++j)
	{
		this->A_appr_[j] -= this->A_[j];
	}

	components.p = this->A_appr_;
	components.pt = this->t_;
}

#pragma warning(pop)