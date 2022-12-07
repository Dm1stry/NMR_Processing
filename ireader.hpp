#ifndef IREADER_HPP
#define IREADER_HPP
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>

struct NMR_Data_1D
{
    QVector<double> t;
    QVector<double> A;
};

class IReader
{
public:
    //IReader();
    virtual NMR_Data_1D Read(const QString &path) = 0;
    //virtual ~IReader() = 0;
};

#endif // READER_HPP
