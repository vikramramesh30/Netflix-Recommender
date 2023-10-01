#include "UserDatabase.h"
#include "User.h"
#include "Recommender.h"
#include "MovieDatabase.h"
#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/vikramramesh/Documents/CS-32/Project4/users.txt";
const string MOVIE_DATAFILE = "/Users/vikramramesh/Documents/CS-32/Project4/movies.txt";



int main()
{
	UserDatabase userdb = UserDatabase();
    userdb.load(USER_DATAFILE);
    MovieDatabase moviedb = MovieDatabase();
    moviedb.load(MOVIE_DATAFILE);
    Recommender r = Recommender(userdb, moviedb);


    vector<MovieAndRank> recommendations = r.recommend_movies("AbFow2483@charter.net", 10);
    User* user = userdb.get_user_from_email("AbFow2483@charter.net");
    cout<< user->get_full_name() << endl;
     if (recommendations.empty())
     cout << "We found no movies to recommend :(.\n";
     else {
         for (int i = 0; i < recommendations.size(); i++) {
             const MovieAndRank& mr = recommendations[i];
             Movie* m = moviedb.get_movie_from_id(mr.movie_id);
             cout << i << ". " << m->get_title() << " ("
             << m->get_release_year() << ")\n Rating: "
             << m->get_rating() << "\n Compatibility Score: "
             << mr.compatibility_score << "\n";
         }
     }
}

