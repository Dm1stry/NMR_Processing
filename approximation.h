#include <nlopt.hpp>

namespace appr_funcs
{
    struct approximation_data
    {
        const std::vector<double>& x_src;
        const std::vector<double>& y_src;
    };

    double exp_n(double t, std::vector<double> params);

    std::vector<double> exp_n(const std::vector<double>& t, std::vector<double> params);

    std::vector<double> d_exp_n(const std::vector<double>& t, std::vector<double> params, unsigned int param_index);

    void d_minimizable(const std::vector<double> &params, std::vector<double> &grad, approximation_data * data, const std::vector<double>& y_current);

    double minimizable(const std::vector<double> &params, std::vector<double> &grad, void* f_data);

    double constrant(const std::vector<double> &params, std::vector<double> &grad, void* f_data);

    std::vector<double> approximate_exp_n(const std::vector<double>& x_src, const std::vector<double>& y_src, const std::vector<double>& lower_bounds, const std::vector<double>& upper_bounds, std::vector<double>& params);

    std::vector<double> approximate_exp_n(const approximation_data& data, const std::vector<double>& lower_bounds, const std::vector<double>& upper_bounds, std::vector<double>& params);

    double polynom(double x, std::vector<double> params);

    std::vector<double> polynom(const std::vector<double>& x, std::vector<double> params);

    std::vector<double> d_polynom(const std::vector<double>& t, std::vector<double> params, unsigned int param_index);

    void d_pol_minimizable(const std::vector<double> &params, std::vector<double> &grad, approximation_data * data, const std::vector<double>& y_current);

    double pol_minimizable(const std::vector<double> &params, std::vector<double> &grad, void* f_data);

    std::vector<double> approximate_pol_n(const std::vector<double>& x_src, const std::vector<double>& y_src, const std::vector<double>& lower_bounds, const std::vector<double>& upper_bounds, std::vector<double>& params);

    std::vector<double> approximate_pol_n(const approximation_data& data, const std::vector<double>& lower_bounds, const std::vector<double>& upper_bounds, std::vector<double>& params);
};