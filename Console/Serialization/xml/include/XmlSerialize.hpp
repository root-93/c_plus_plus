#pragma once

#include <fstream> //std::ofstream

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>



namespace xml{
    template <class T>
    static void save(const T &t, const char *fileName) noexcept;

    template <class T>
    static void restore(T &t, const char *fileName) noexcept;
}


template <class T>
static void xml::save(T &t, const char *fileName) noexcept{
    std::ofstream ofs{fileName};
    assert(ofs.good());
    boost::archive::xml_oarchive oa{ofs};
    oa << BOOST_SERIALIZATION_NVP(t);
    // try{
    //     oa << BOOST_SERIALIZATION_NVP(t);
    // }
    // catch(std::exception const &ex){
    //     std::cerr << ex.what() << std::endl;
    // }
}


template <class T>
static void xml::restore(T &t, const char *fileName) noexcept{
    std::ifstream ifs(fileName);
    assert(ifs.good());
    boost::archive::xml_iarchive ia{ifs};
    ia >> BOOST_SERIALIZATION_NVP(t);
    // try{
    //     ia >> BOOST_SERIALIZATION_NVP(t);
    // }
    // catch(std::exception const &ex){
    //     std::cerr << ex.what() << std::endl;
    // }
}    
