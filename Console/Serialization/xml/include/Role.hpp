#pragma once
#include <boost/serialization/access.hpp>
#include <string>

class Role{
    public:
        friend class boost::serialization::access;

        Role() = default;
        Role(std::pair<std::string, std::string> pair) : _pair{pair} {}
        Role(std::string first, std::string second) : _pair{first, second} {}
        ~Role(){}

        const std::string name()const {
            return _pair.first;
        }

        const std::string role()const {
            return _pair.second;
        }

    private:
        template<class Archive>
        void serialize(Archive &ar,[[maybe_unused]]const unsigned int version) {            
            ar & BOOST_SERIALIZATION_NVP(_pair.first);
            ar & BOOST_SERIALIZATION_NVP(_pair.second);
        }

        std::pair<std::string, std::string> _pair {};        
};