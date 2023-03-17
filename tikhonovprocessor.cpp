#include "tikhonovprocessor.h"

TikhonovProcessor::TikhonovProcessor() : K_(nullptr), s_(nullptr), r_(nullptr), t_() {}

TikhonovProcessor::~TikhonovProcessor()
{
    delete K_;
    delete s_;
    delete r_;
    K_ = nullptr;
    s_ = nullptr;
    r_ = nullptr;
}

void TikhonovProcessor::Process(Data& data)
{
    using namespace Eigen;
    int iterations = 1000;
    alfa_ = 20;
    int p_quantity = 10000;
    double Tmin = 1e-7;;
    QVector<double> A = data.getAmplitudes();
    t_ = data.getTimes();
    double Tmax = *t_.end();
    QVector<double> p(p_quantity, 0);
    double log_p_max = std::log10(1/Tmin);
    double log_p_min = std::log10(1/Tmax);
    double step = (log_p_max - log_p_min) / p_quantity;
    //Создаем логарифмическое пространство
    for(int i = 0; i < p_quantity; ++i)
    {
        p[i] += std::pow(10, log_p_min + i * (step));
    }
    //Создаем и наполняем матрицу K_
    K_ = new MatrixXd(p_quantity, t_.size());
    for(int p_index = 0; p_index < p_quantity; ++p_index)
    {
        for(int t_index = 0; t_index < t_.size(); ++t_index)
        {
            (*K_)(p_index, t_index) = std::exp(-p[p_index] * t_[t_index]);
        }
    }
    MatrixXd K_t((*K_).transpose());
    r_ = new VectorXd(p_quantity);
    s_ = new VectorXd(t_.size());
    QVector<double> (p_quantity, 0);

    MatrixXd W((K_t * (*K_) + alfa_ * MatrixXd::Identity(p_quantity, p_quantity)).inverse());
    MatrixXd K_t_s(K_t * (*s_));
    while(iterations--)
    {
        (*r_) = W * (K_t_s + alfa_ * (*r_));
        for(auto &r : (*r_))
        {
            r = r < 0 ? 0 : r;
        }
    }
}

QPair<QVector<double>, QVector<double>> TikhonovProcessor::getApproximatedCurve() const
{
    Eigen::VectorXd approximated((*K_) * (*r_));
    QVector<double> returnable(approximated.data(), approximated.data() + approximated.size());
    return {t_, returnable};
}

QPair<QVector<double>, QVector<double>>  TikhonovProcessor::getSpectrum() const
{
    return {{0}, {0}}; //Заглушка - переделать
}
