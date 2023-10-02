#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H
#include <vector>

double trapz_intergal(std::vector<double> x, std::vector<double> y);

template<class RandomIt> 
inline double trapz_intergal(RandomIt x_begin, RandomIt x_end, RandomIt y_begin, RandomIt y_end)
{
    if(x_begin == x_end || x_end - x_begin != y_end - y_begin)
    {
        return 0;
    }
    double sum = (*y_begin) * (*(x_begin + 1) - (*x_begin)) / 2;
    for(; x_begin < x_end - 1; x_begin++, y_begin++)
    {
        sum += (*y_begin) * (*(x_begin + 1) - (*x_begin));
    }
    sum += *(y_end - 1) * (*(x_end - 1) - *(x_end - 2));

    return sum;
}

template<class RandomIt>
inline std::vector<size_t> argmax(RandomIt x_begin, RandomIt x_end)
{
    if(x_begin == x_end)
    {
        return {};
    }
    std::vector<size_t> peaks;
    for(auto x_current = x_begin + 1; x_current < x_end - 1; ++x_current)
    {
        if(*x_current > *(x_current - 1) && *x_current > *(x_current + 1))
        {
            peaks.push_back(x_current - x_begin);
        }
    }
    return peaks;
}

std::vector<double> logspace(double start, double stop, size_t number, double base = 10.0, bool endpoint = true);
#endif