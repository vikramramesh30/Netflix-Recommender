#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <unordered_map>
#include <algorithm>

#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
   m_movieDatabase = &movie_database;
   m_userDatabase = &user_database;


}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if(movie_count <= 0) {
    return vector<MovieAndRank>();
}

unordered_map<string, int> movieRankings;
vector<MovieAndRank> recommendations;

User* user = m_userDatabase->get_user_from_email(user_email);
if(user == nullptr) {
    return vector<MovieAndRank>();
}

vector<string> watchHistory = user->get_watch_history();
unsigned long numWatched = watchHistory.size();

for(int i = 0; i < numWatched; i++){
    string movieId = watchHistory[i];
    Movie* movie = m_movieDatabase->get_movie_from_id(movieId);

    vector<string> directors = movie->get_directors();
    for(int j = 0; j < directors.size(); j++){
        vector<Movie*> moviesWithDirector = m_movieDatabase->get_movies_with_director(directors[j]);
        for(int k = 0; k < moviesWithDirector.size(); k++){
            movieRankings[moviesWithDirector[k]->get_id()] += 20;
        }
    }

    vector<string> actors = movie->get_actors();
    for(int j = 0; j < actors.size(); j++){
        vector<Movie*> moviesWithActor = m_movieDatabase->get_movies_with_actor(actors[j]);
        for(int k = 0; k < moviesWithActor.size(); k++){
            movieRankings[moviesWithActor[k]->get_id()] += 30;
        }
    }

    vector<string> genres = movie->get_genres();
    for(int j = 0; j < genres.size(); j++){
        vector<Movie*> moviesWithGenre = m_movieDatabase->get_movies_with_genre(genres[j]);
        for(int k = 0; k < moviesWithGenre.size(); k++){
            movieRankings[moviesWithGenre[k]->get_id()] += 1;
        }
    }
}

for(auto it = movieRankings.begin(); it != movieRankings.end(); it++){
    if(!checkWatch(watchHistory, it->first)){
        recommendations.push_back(MovieAndRank(it->first, it->second));
    }
}

sort(recommendations.begin(), recommendations.end(), [this] (const MovieAndRank& a, const MovieAndRank& b){
    if (a.compatibility_score != b.compatibility_score)
    {
        return a.compatibility_score > b.compatibility_score;
    }
    Movie* movieA = m_movieDatabase->get_movie_from_id(a.movie_id);
    Movie* movieB = m_movieDatabase->get_movie_from_id(b.movie_id);
    if (movieA->get_rating() != movieB->get_rating()){
        return movieA->get_rating() > movieB->get_rating();
    }
    else
        return movieA->get_title() < movieB->get_title();
    }
);

vector<MovieAndRank>::const_iterator first = recommendations.begin();
vector<MovieAndRank>::const_iterator last = recommendations.begin() + movie_count;
vector<MovieAndRank> newRecommendations(first, last);

return newRecommendations;
}


bool Recommender::checkWatch(std::vector<std::string> watch_history, std::string id) const{
    for(int i = 0; i < watch_history.size(); i++){
        if(watch_history[i] == id) return true;
    }
    return false;
}
