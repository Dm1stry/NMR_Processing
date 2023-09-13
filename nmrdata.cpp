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
        emit dataUpdated(this->t_, this->A_);
    }
}

void NMRData::setData(QVector<double> A, QVector<double> t)
{
    if(A.size() == t.size())
    {
        this->A_ = A;
        this->t_ = t;
    }
    else
    {
        emit wrongData();
    }
}