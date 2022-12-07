#ifndef NMR_READER_HPP
#define NMR_READER_HPP
#include "ireader.hpp"

class nmr_reader : public IReader
{
public:
    nmr_reader();
    NMR_Data_1D Read(const QString &path);
};

#endif // NMR_READER_HPP
