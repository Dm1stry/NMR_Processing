#include "data.h"

//Data::Data(QVector<double> A, QVector<double> t) : A_(A), t_(t) {}

Data::Data() : data_type_(ExperimentType::empty) {}

bool Data::readAsCPMG(QString path)
{
    data_type_ = ExperimentType::CPMG;
    QFile nmr_file(path);
    if (!nmr_file.open(QIODevice::ReadOnly))
    {
        return false;
    }
   //QTextStream counter(&nmr_file);
   size_t line_count = 1000;
   /*while (!counter.atEnd())
   {
      counter.readLine();
      ++line_count;
   }*/

   t_.reserve(line_count);
   A_.reserve(line_count);
   QTextStream in(&nmr_file);
   QRegExp rx("( |\\t)");
   bool ok;
   while (!in.atEnd())
   {
      QString line = in.readLine();
      while(*(line.begin()) == ' ')
      {
          line.remove(0, 1);
      }
      while(*(line.end() - 1) == ' ')
      {
          line.remove(-1, 1);
      }
      line.replace("  ", " ");
      QStringList splitted = line.split(rx);
      double tmp = splitted[0].toDouble(&ok);
      if(ok)
        t_.push_back(tmp);
      else
        t_.push_back(2);
      tmp = splitted[1].toDouble(&ok);
      if(ok)
        A_.push_back(tmp);
      else
        A_.push_back(2);
   }
   A_.shrink_to_fit();
   t_.shrink_to_fit();
   nmr_file.close();
   return true;
}

QVector<double> Data::getAmplitudes() const
{
    return A_;
}

QVector<double> Data::getTimes() const
{
    return t_;
}
