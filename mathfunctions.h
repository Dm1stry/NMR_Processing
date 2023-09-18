#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H
#include <vector>


double trapz_intergal(std::vector<double> x, std::vector<double> y);

inline std::vector<double> logspace(double start, double stop, size_t number, double base = 10.0, bool endpoint = true);

#endif