#pragma once
#include <string>
#include <vector>
#include <iomanip>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

#include "Role.hpp"

#define actors std::vector<Role>

struct Movie{
    private:
        //using actors = std::vector<Pair>;
        using people = std::vector<std::string>;
    public:
        friend class boost::serialization::access;
        
        Movie(int ID = 0, std::string tit = "no title", int year = 0, int len = 0) 
            : ID{ID}, title{tit}, publishYear{year}, lenght{len} {}
        Movie(int ID, std::string tit, int year, int len, people dir, people wri, actors cast) 
            : Movie(ID, tit, year, len) {
                this->directors = dir;
                this->writers = wri;
                this->cast = cast;
            }


        int             ID {};
        std::string     title = "no title";
        int             publishYear {};
        int             lenght {}; //[min]
        people          directors {};    
        people          writers {};
        actors          cast {};
        std::string     toString()const noexcept;

    private:

        template<class Archive>
        void serialize(Archive &ar, [[maybe_unused]]const unsigned int version) {
            /*BOOST_SERIALIZATION_NVP is needed for xml serialization to generate tag name*/
            ar & BOOST_SERIALIZATION_NVP(ID);
            ar & BOOST_SERIALIZATION_NVP(title);
            ar & BOOST_SERIALIZATION_NVP(publishYear);
            ar & BOOST_SERIALIZATION_NVP(lenght);

            ar & BOOST_SERIALIZATION_NVP(directors);
            ar & BOOST_SERIALIZATION_NVP(writers);
            ar & BOOST_SERIALIZATION_NVP(cast);
            
        }

    public:

};

inline std::string Movie::toString()const noexcept{
        constexpr int width = 15;

        std::stringstream ss;

        ss  << std::endl << std::string(60,'*') << std::endl
            << std::left << std::setw(width) << "ID:" << ID << std::endl
            << std::left << std::setw(width) << "Title:" << title << std::endl
            << std::left << std::setw(width) << "Year:" << publishYear << std::endl
            << std::left << std::setw(width) << "Lenght [min]:" << lenght << std::endl;
        
        
        ss << "Directors:\n"; 
        for (auto &&s : directors){
            ss << "\t" + s + "\n";
        }

        ss << "Writers:\n";
        for (auto &&s : writers){
            ss << "\t" + s + "\n";
        }

        ss << "Cast:\n";
        for (auto &s : cast){
            ss << "\t" << std::setw(35) << "star: " + s.name() << "name: " + s.role() + "\n";
        }
        return ss.str();
 }



/* use when serialize finction can not be member of Movie
namespace boost {
namespace serialization{
    template<class Archive>
    void serialize (Archive &ar, Movie &movie, const unsigned int version){
            ar & movie.ID;
            ar & movie.title;
            ar & movie.lenght;

            ar & movie.directors;
            ar & movie.writers;
            ar & movie.cast;
            
            // for (auto &&s : movie.directors){ ar & s;}
            // for (auto &&s : movie.writers){ar & s;}
            // for (auto &&s : movie.cast) { 
            //     ar & s.first;
            //     ar & s.second;
            // }
    }
}
}
*/