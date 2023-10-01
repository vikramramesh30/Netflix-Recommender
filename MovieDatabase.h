#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

using namespace std;

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    bool m_loaded = false;
    std::vector<Movie*> movies;
    TreeMultimap<std::string, Movie*> m_idTree;
    TreeMultimap<std::string, Movie*> m_directorTree;
    TreeMultimap<std::string, Movie*> m_actorTree;
    TreeMultimap<std::string, Movie*> m_genreTree;
    
    void transform(string tempString, vector<string>&tempVector);
};

#endif 