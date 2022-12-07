#include "nmr_reader.hpp"



nmr_reader::nmr_reader() {}

NMR_Data_1D nmr_reader::Read(const QString &path)
{
    QFile nmr_file(path);
    NMR_Data_1D result;
    if (nmr_file.open(QIODevice::ReadOnly))
    {
       //QTextStream counter(&nmr_file);
       size_t line_count = 1000;
       /*while (!counter.atEnd())
       {
          counter.readLine();
          ++line_count;
       }*/

       result.t.reserve(line_count);
       result.A.reserve(line_count);
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
            result.t.push_back(tmp);
          else
            result.t.push_back(2);
          tmp = splitted[1].toDouble(&ok);
          if(ok)
            result.A.push_back(tmp);
          else
            result.A.push_back(2);
       }
       nmr_file.close();
    }
    else
    {
        result.t = {0};
        result.A = {0};
    }
    return result;
}
