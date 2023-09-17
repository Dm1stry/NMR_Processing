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
                splitted_line = line.split(spaces);
                this->A_.push_back(splitted_line[1].toDouble());
                this->t_.push_back(splitted_line[0].toDouble());
            }
        }
        file.close();
        this->A_.shrink_to_fit();
        this->t_.shrink_to_fit();
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

void NMRData::clearData()
{
    this->clearRawData();
    this->clearProcessedData();
}