#pragma once

#include <fstream> //std::ofstream
#include <iostream>
#include <fstream>
#include <iomanip>

#include <cstdio>
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
    namespace std{
        using::remove;
    }
#endif

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


// namespace xml{
//     void saveXml(const Movie &movie, const char *fileName) noexcept;
//     void restoreXml(Movie &movie, const char *fileName);
// };

template <class T>
void saveToXml(const T &t, const char *fileName) noexcept{
    std::ofstream ofs{fileName};
    assert(ofs.good());
    boost::archive::xml_oarchive oa{ofs};
    oa << BOOST_SERIALIZATION_NVP(t);
}


template <class T>
void restoreFromXml(T &t, const char *fileName) noexcept{
    std::ifstream ifs(fileName);
    assert(ifs.good());
    boost::archive::xml_iarchive ia{ifs};
    ia >> BOOST_SERIALIZATION_NVP(t);
}