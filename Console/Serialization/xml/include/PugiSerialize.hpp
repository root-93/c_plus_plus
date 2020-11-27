#pragma once
#include <string>
#include <string_view>

#include "pugixml.hpp"
#include "Movie.hpp"

using MovieList = std::vector<Movie>;


class PugiSerialize {
    public:
        static void        serialize(MovieList const &movies, std::string filepath);
        static MovieList   deserialize(std::string filepath);
};


inline void PugiSerialize::serialize(MovieList const &movies, std::string filepath){
    pugi::xml_document doc;
    auto root = doc.append_child("movies");

    for (auto &&s : movies){
        auto movieNode = root.append_child("movie");

        movieNode.append_attribute("ID").set_value(s.ID);
        movieNode.append_attribute("title").set_value(s.title.c_str());
        movieNode.append_attribute("year").set_value(s.publishYear);
        movieNode.append_attribute("lenght").set_value(s.lenght);

        auto castNode = movieNode.append_child("cast");
        for (auto &&c : s.cast){
            auto node = castNode.append_child("role");
            node.append_attribute("star").set_value(c.name().c_str());
            node.append_attribute("name").set_value(c.role().c_str());
        }

        auto directorsNode = movieNode.append_child("directors");
        for (auto &&d : s.directors){
            directorsNode.append_child("director")
                         .append_attribute("name")
                         .set_value(d.c_str());
        }
        

        auto writersNode = movieNode.append_child("writers");
        for (auto &&w : s.writers){
            writersNode.append_child("writer")
                       .append_child("name")
                       .set_value(w.c_str());

        }
    }

    doc.save_file(filepath.c_str());
}

MovieList PugiSerialize::deserialize(std::string filePath){
    pugi::xml_document doc;
    MovieList movies;

    auto result = doc.load_file(filePath.c_str());
    if(result){
        auto root = doc.child("movies");
        for (auto movieNode = root.child("movie"); movieNode; movieNode = movieNode.next_sibling("movie")){
            Movie movie;
            movie.ID = movieNode.attribute("ID").as_uint();
            movie.title = movieNode.attribute("title").as_string();
            movie.publishYear = movieNode.attribute("year").as_uint();
            movie.lenght = movieNode.attribute("lenght").as_uint();

            for (auto &&roleNode : movieNode.child("cast").children("role")){
                movie.cast.push_back(Role(roleNode.attribute("star").as_string(),
                                                roleNode.attribute("name").as_string()));
            }

            for (auto &&directorNode : movieNode.child("directors").children("director")){
                movie.directors.push_back(directorNode.attribute("name").as_string());
            }

            for (auto &&writerNode : movieNode.child("writers").children("writer")){
                movie.writers.push_back(writerNode.attribute("name").as_string());
            }
                        
            movies.push_back(movie);
        }
    }
    return movies;
}