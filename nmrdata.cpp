#include "nmrdata.h"

NMRData::NMRData(QObject * parent /*= nullptr*/)
  : QObject(parent)
{

}

void NMRData::readAsCPMG(const QString& filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream filestream(&file);
        QString line;
        QStringList splitted_line;
        QRegExp spaces("(\\s+)");
        this->A_.reserve(10000);
        this->t_.reserve(10000);
        while (!filestream.atEnd())
        {
            line = filestream.readLine();
            line = line.trimmed();
            if(line.begin() != line.end())
            {
                line.replace(',', '.');
                splitted_line = line.split(spaces);
                bool A_converted = false;
                double A_value = splitted_line[1].toDouble(&A_converted);
                bool t_converted = false;
                double t_value = splitted_line[0].toDouble(&t_converted);
                if(A_converted && t_converted)
                {
                    this->A_.push_back(A_value);
                    this->t_.push_back(t_value);
                }
            }
        }
        file.close();
        this->A_.shrink_to_fit();
        this->t_.shrink_to_fit();

        double max_element = *std::min_element(this->A_.begin(), this->A_.end());
        for(auto A_it = A_.begin(); A_it < A_.end(); ++A_it)
        {
            *A_it = *A_it - max_element; 
        }

        max_element = *std::max_element(this->A_.begin(), this->A_.end());
        for(auto A_it = A_.begin(); A_it < A_.end(); ++A_it)
        {
            *A_it = *A_it / max_element; 
        }
        
        
        NMRDataStruct raw_data;
        raw_data.A = A_;
        raw_data.t = t_;
        raw_data.p = {};
        raw_data.pt = {};
        emit rawDataUpdated(raw_data);
    }
}

void NMRData::setRawData(const NMRDataStruct& raw_data)
{
    if(raw_data.A.size() == raw_data.t.size())
    {
        this->A_ = raw_data.A;
        this->t_ = raw_data.t;
        emit rawDataUpdated(raw_data);
    }
    else
    {
        emit wrongData();
    }
}

void NMRData::setProcessedData(const NMRDataStruct& processed_data)
{
    this->A_approximated_ = processed_data.A;
    this->t_approximated_ = processed_data.t;
    this->p_ = processed_data.p;
    this->pt_ = processed_data.pt;

    emit processedDataUpdated(processed_data);
}

void NMRData::setComponents(const NMRDataStruct& components)
{
    M_ = components.A;
    T_ = components.t;

    emit componentsUpdated(components);
}

void NMRData::setNoise(const NMRDataStruct& components)
{
    noise_ = components.p;
}

void NMRData::clearRawData()
{
    this->A_.clear();  //Однако память выделенная под вектор не освобождается, чтобы при считывании новых данных не выделять паямть заного.
    this->t_.clear();

    NMRDataStruct raw_data = {
        .A=this->A_,
        .t=this->t_
    };
    emit rawDataUpdated(raw_data);
}

void NMRData::clearProcessedData()
{
    this->A_approximated_.clear();
    this->A_approximated_.clear();
    this->p_.clear();
    this->pt_.clear();

    NMRDataStruct processed_data = {
        .A = this->A_approximated_,
        .t = this->t_approximated_,
        .p = this->p_,
        .pt = this->pt_
    };
    emit processedDataUpdated(processed_data);
}

void NMRData::clearComponents()
{
    this->M_.clear();
    this->T_.clear();

     NMRDataStruct components = {
        .A = this->M_,
        .t = this->T_
    };

    emit componentsUpdated(components);
}

void NMRData::clearData()
{
    this->clearRawData();
    this->clearProcessedData();
    this->clearComponents();
}