#include <nlopt.hpp>
#include <stdint.h>
#include <cmath>
#pragma warning(push)
#pragma warning(disable : 4267)

namespace appr_funcs
{
    struct approximation_data
    {
        const std::vector<double>& x_src;
        const std::vector<double>& y_src;
    };

    double exp_n(double t, std::vector<double> params)
    {
        double y = 0;
        for(size_t n = 0; n < params.size(); n += 2)
        {
            y += params[n] * exp((double)(-t / params[n + 1]));
        }
        return y;
    }

    std::vector<double> exp_n(const std::vector<double>& t, std::vector<double> params)
    {
        std::vector<double> y(t.size(), 0);
        for(size_t n = 0; n < params.size(); n += 2)
        {
            for(size_t i = 0; i < t.size(); ++i)
            {
                y[i] += params[n] * exp((double)(-t[i] / params[n + 1]));
            }
        }
        return y;
    }

    std::vector<double> d_exp_n(const std::vector<double>& t, std::vector<double> params, unsigned int param_index)
    {
        size_t n = params.size();

        for(unsigned int i = 0; i < n; i+= 2)
        {
            if(i != param_index || i != param_index - 1)
            {
                params[i] = 0;
                params[i + 1] = 1;
            }
            if(i == param_index)
            {
                params[i] = 1;
            }
        }
        
        if(param_index % 2 == 0)
        {
            return exp_n(t, params);
        }
        else
        {
            std::vector<double> result = exp_n(t, params);
            double coeff = (1 / (params[param_index] * params[param_index]));
            auto t_it = t.begin();

            for(auto result_it = result.begin(); result_it < result.end(); ++result_it, ++t_it)
            {
                *result_it *= *t_it * coeff;
            }
            return result;
        }
    }

    void d_minimizable(const std::vector<double> &params, std::vector<double> &grad, approximation_data * data, const std::vector<double>& y_current)
    {
        if(!grad.empty())
        {
            for(unsigned int i = 0; i < grad.size(); ++i)
            {
                grad[i] = 0;
                std::vector<double> d_exp = d_exp_n(data->x_src, params, i);
                for(size_t j = 0; j < data->x_src.size(); ++j)
                {
                    double tmp = y_current[j] - data->y_src[j];
                    grad[i] += 2 * tmp * d_exp[j];
                }
                // = d_exp_n(data->x_src, params, i);
            }
        }
    }

    double minimizable(const std::vector<double> &params, std::vector<double> &grad, void* f_data)
    {
        static approximation_data * data = static_cast<approximation_data*>(f_data);
        static const size_t n = data->y_src.size();
        double sum = 0;
        std::vector<double> y_current = exp_n(data->x_src, params);
        //Possible to parallize
        for(int i = 0; i < n; ++i)
        {
            double tmp = y_current[i] - data->y_src[i];  //log(a - b)
            sum += tmp * tmp;
        }
        d_minimizable(params, grad, data, y_current);
        return sum / (n - 1);
    }

    double constrant(const std::vector<double> &params, std::vector<double> &grad, void* f_data)
    {
        double sum = 0;
        for(int i = 0; i < params.size(); i+=2)
        {
            sum += params[i];
        }
        sum -= 1;
        return sum * sum;
    }

    std::vector<double> approximate_exp_n(const approximation_data& data, const std::vector<double>& lower_bounds, const std::vector<double>& upper_bounds, std::vector<double>& params)
    {
        nlopt::opt optimizer(nlopt::algorithm::LN_COBYLA, params.size());
        optimizer.set_min_objective(minimizable, (void*)(&data));
        optimizer.set_lower_bounds(lower_bounds);
        optimizer.set_upper_bounds(upper_bounds);
        optimizer.add_equality_constraint(constrant, NULL, 0.001);
        std::vector<double> grad;
        optimizer.set_ftol_rel(0.01);

        double result_func_value = -1;
        nlopt::result result = optimizer.optimize(params, result_func_value);

        return params;
    }

    std::vector<double> approximate_exp_n(const std::vector<double>& x_src, const std::vector<double>& y_src, const std::vector<double>& lower_bounds, const std::vector<double>& upper_bounds, std::vector<double>& params)
    {
        approximation_data data{
        .x_src = x_src,
        .y_src = y_src
        };

        return approximate_exp_n(data, lower_bounds, upper_bounds, params);
    }

    double polynom(double x, std::vector<double> params)
    {
        double result = 0;
        for(uint8_t i = 0; i < params.size(); ++i)
        {
            result += pow(x, i) * params[i];
        }
        return result;
    }

    std::vector<double> polynom(const std::vector<double>& x, std::vector<double> params)
    {
        const size_t n = x.size();
        std::vector<double> result(n, 0);
        for(uint8_t i_param = 0; i_param < params.size(); ++i_param)
        {
            for(int i_x = 0; i_x < n; ++i_x)
            {     
                result[i_x] += pow(x[i_x], i_param) * params[i_param];
            }
        }
        return result;
    }

    std::vector<double> d_polynom(const std::vector<double>& x, std::vector<double> params, unsigned int param_index)
    {
        const size_t n = x.size();
        std::vector<double> result(n, 1);
        if(param_index == 0)
        {
            return result;
        }
        for(int i = 0; i < n; ++i)
        {
            result[i] = pow(x[i], i);
        }
        return result;
    }

    void d_pol_minimizable(const std::vector<double> &params, std::vector<double> &grad, approximation_data * data, const std::vector<double>& y_current)
    {
        if(!grad.empty())
        {
            for(unsigned int i = 0; i < grad.size(); ++i)
            {
                grad[i] = 0;
                std::vector<double> d_pol = d_polynom(data->x_src, params, i);
                std::vector<double> pol = polynom(data->x_src, params);
                for(size_t j = 0; j < data->x_src.size(); ++j)
                {
                    double tmp = y_current[j] - data->y_src[j];
                    grad[i] += 2 * tmp * d_pol[j] / pol[j];
                }
                // = d_exp_n(data->x_src, params, i);
            }
        }
    }

    double pol_minimizable(const std::vector<double> &params, std::vector<double> &grad, void* f_data)
    {
        static approximation_data * data = static_cast<approximation_data*>(f_data);
        static const size_t n = data->y_src.size();
        double sum = 0;
        std::vector<double> y_current = polynom(data->x_src, params);
        //Possible to parallize
        for(int i = 0; i < n; ++i)
        {
            double tmp = log(abs(y_current[i] - data->y_src[i]) + 1e-10);  //log(a - b)
            sum += tmp * tmp;
        }
        d_pol_minimizable(params, grad, data, y_current);
        return sum / (n - 1);
    }

    std::vector<double> approximate_pol_n(const approximation_data& data, std::vector<double>& params)
    {
        nlopt::opt optimizer(nlopt::algorithm::LN_COBYLA, params.size());
        optimizer.set_min_objective(pol_minimizable, (void*)(&data));
        //optimizer.add_equality_constraint(constrant, NULL, 0.001);
        std::vector<double> grad;
        optimizer.set_ftol_rel(0.01);

        double result_func_value = -1;
        nlopt::result result = optimizer.optimize(params, result_func_value);

        return params;
    }

    std::vector<double> approximate_pol_n(const std::vector<double>& x_src, const std::vector<double>& y_src, std::vector<double>& params)
    {
        const approximation_data data{
        .x_src = x_src,
        .y_src = y_src
        };

        return approximate_pol_n(data, params);
    }

};

#pragma warning(pop)