#include "mathfunctions.h"

inline double trapz_intergal(std::vector<double> x, std::vector<double> y)
{
    if(x.begin() == x.end() || x.size() != y.size())
    {
        return 0;
    }
    size_t last_index = x.size() - 1;
    double sum = y[0] * (x[1] - x[0]) / 2;
    for(size_t i = 1; i < last_index; ++i)
    {
        sum += y[i] * (x[i + 1] - x[i]);
    }
    sum +=  y[last_index] * (x[last_index] - x[last_index - 1]);

    return sum;
}

inline std::vector<double> logspace(double start, double stop, size_t number, double base, bool endpoint)
{
    std::vector<double> space;
    space.resize(number);
    double step = (stop - start) / (number - int(endpoint));
    for(size_t i = 0; i < number; ++i)
    {
        space[i] = pow(base, start);
        start += step;
    }
    return space;
}

