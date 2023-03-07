#include "tikhonovprocessor.h"
#include <algorithm>
#include <iostream>

TikhonovProcessor::TikhonovProcessor() : K_(nullptr), s_(nullptr), r_(nullptr), t_(nullptr) {}

TikhonovProcessor::~TikhonovProcessor()
{
    delete K_;
    delete s_;
    delete r_;
    delete t_;
    K_ = nullptr;
    s_ = nullptr;
    r_ = nullptr;
    t_ = nullptr;
}

void TikhonovProcessor::Process(const Data& data)
{
    alfa_ = 20;
    int p_quantity = 10000;
    double Tmin = 1e-7;;
    QVector<double> A = data.getAmplitudes();
    QVector<double> t = data.getTimes();
    double Tmax = *std::max(t.begin(), t.end());
    QVector<double> p(p_quantity, 0);
    double log_p_max = std::log10(1/Tmin);
    double log_p_min = std::log10(1/Tmax);
    double step = (log_p_max - log_p_min) / p_quantity;
    for(int i = 0; i < p_quantity; ++i)
    {
        p[i] += std::pow(10, log_p_min + i * (step));
        std::cout << p[i] << ' ';
    }

}
