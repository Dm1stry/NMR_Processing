#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H
#include <vector>
#include <map>
#include <cmath>

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


/*
* Returns vector of local maximums in collection
*/
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


/*
* Returns vector of local minimums in collection
*/
template<class RandomIt>
inline std::vector<size_t> argmin(RandomIt x_begin, RandomIt x_end)
{
    if(x_begin == x_end)
    {
        return {};
    }
    std::vector<size_t> peaks;
    for(auto x_current = x_begin + 1; x_current < x_end - 1; ++x_current)
    {
        if(*x_current < *(x_current - 1) && *x_current < *(x_current + 1))
        {
            peaks.push_back(x_current - x_begin);
        }
    }
    return peaks;
}

template<class RandomIt>
inline std::vector<size_t> argmineq(RandomIt x_begin, RandomIt x_end)
{
    if(x_begin == x_end)
    {
        return {};
    }
    if(x_end - x_begin == 1)
    {
        return {0};
    }
    std::vector<size_t> peaks;
    if(*x_begin < *(x_begin + 1))
    {
        peaks.push_back(0);
    }
    for(auto x_current = x_begin + 1; x_current < x_end - 1; ++x_current)
    {
        if(*x_current < *(x_current - 1) && *x_current <= *(x_current + 1) || *x_current <= *(x_current - 1) && *x_current < *(x_current + 1))
        {
            peaks.push_back(x_current - x_begin);
        }
    }
    if((x_end - 2) >= x_begin && *(x_end - 1) < *(x_end - 2))
    {
        peaks.push_back((x_end - x_begin) - 1);
    }
    return peaks;
}


/*
* Returns iterator that points on element of the collection, that is greater then the given value and nearest to it
* if there is no element like that, returns end iterator
*/
template<class Item, class Iterator>
inline Iterator find_nearest_greater(const Item& value, Iterator x_begin, Iterator x_end)
{
    if(x_begin == x_end || *(x_end - 1) <= value)
    {
        return x_end;
    }
    for(auto x_current = x_begin; x_current < x_end; ++x_current)
    {
        if(*x_current > value)
        {
            return x_current;
        }
    }
    return x_end;
}


/*
* Returns iterator that points on element of the collection, that is less then the given value and nearest to it
* if there is no element like that, returns end iterator
*/
template<class Item, class Iterator>
inline Iterator find_nearest_less(const Item& value, Iterator x_begin, Iterator x_end)
{
    if(x_begin == x_end || *(x_begin) >= value)
    {
        return x_end;
    }
    for(auto x_current = x_end - 1; x_current >= x_begin; --x_current)
    {
        if(*x_current < value)
        {
            return x_current;
        }
    }
    return x_end;
}

std::vector<double> logspace(double start, double stop, size_t number, double base = 10.0, bool endpoint = true);

int get_power(double num);
#endif