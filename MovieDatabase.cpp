#include "MovieDatabase.h"
#include "Movie.h"

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>


using namespace std;

MovieDatabase::MovieDatabase()
{
    m_loaded = false;
}
MovieDatabase::~MovieDatabase(){
    for(int i = 0; i < movies.size(); i++){
        delete movies.at(i);
    }
}

void MovieDatabase::transform(string tempString, vector<string>& tempVector)
{ 
    unsigned long n = tempString.size();
    string name;
    for(int i = 0; i < n; i++)
     {
        if(tempString[i] == ',')
        {
            tempVector.push_back(name);
             name = "";
        }
        else
        {
          name = name + tempString[i];
        }
        }

        if(name != "")
        {
            tempVector.push_back(name);
        }
        
        return;
 }

bool MovieDatabase::load(const string& filename)
{
    if(m_loaded)
    {
        return false;
    }
    ifstream infile(filename);    
    if ( ! infile )                
    {
        return false;
    }
    
    string id;
    while (getline(infile, id))
    {
        string movie;
        getline(infile, movie);
        string year;
        getline(infile, year);
        
        string director;
        vector<string> directors;
        getline(infile, director);
        transform(director, directors);
        
        string actor;
        vector<string> actors;
        getline(infile, actor);
        transform(actor, actors);
        
        string genre; 
        vector<string> genres;
        getline(infile, genre);
        transform(genre, genres);
        
        float rating;
        infile >> rating;
        infile.ignore(10000, '\n');
        
        
        string foo;
        getline(infile, foo);
        
        Movie* newmovie =  new Movie(id, movie, year, directors, actors, genres, rating);
        movies.push_back(newmovie);


        for(int i = 0; i < id.size(); i++){
            id[i] = tolower(id[i]);
        }
        
        m_idTree.insert(id, newmovie);
        
        for(int i = 0; i < directors.size(); i++)
        {
            string temp_string = directors[i];
            for(int j = 0; j < temp_string.size(); j++){
                temp_string[j] = tolower(temp_string[j]);
            }
            m_directorTree.insert(temp_string, newmovie);
        }

        for(int i = 0; i < actors.size(); i++)
        {
            string temp_string = actors[i];
            for(int j = 0; j < temp_string.size(); j++){
                temp_string[j] = tolower(temp_string[j]);
            }
            m_actorTree.insert(temp_string, newmovie);
        }
            
        for(int i = 0; i < genres.size(); i++)
        {
            string temp_string = genres[i];
            for(int j = 0; j < temp_string.size(); j++){
                temp_string[j] = tolower(temp_string[j]);
            }
            m_genreTree.insert(genres[i], newmovie);
        }
            
        
    }
    
    m_loaded = true;
    return true;

}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string s = id;
    for(int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
    }
    TreeMultimap<std::string, Movie*>::Iterator it = m_idTree.find(s);
    if(it.is_valid()){
        return it.get_value();
    }
    else return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string s = director;
    for(int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
    }
    TreeMultimap<std::string, Movie*>::Iterator it = m_directorTree.find(s);
    vector<Movie*> tempv;
    while (it.is_valid()) {
        tempv.push_back(it.get_value());
        it.advance();
    }
    return tempv;  
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string s = actor;
    for(int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
    }

    TreeMultimap<std::string, Movie*>::Iterator it = m_actorTree.find(s);
    vector<Movie*> tempv;

    while (it.is_valid()) 
    {
        tempv.push_back(it.get_value());
        it.advance();
    }
    return tempv;  
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string s = genre;

    for(int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
    }

    TreeMultimap<std::string, Movie*>::Iterator it = m_genreTree.find(s);
    vector<Movie*> tempv;

    while (it.is_valid()) 
    {
        tempv.push_back(it.get_value());
        it.advance();
    }
    return tempv;  
}
