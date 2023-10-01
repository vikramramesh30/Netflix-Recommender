#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
    m_loaded = false;
}

bool UserDatabase::load(const string& filename)
{
    if(m_loaded)
    {
        return false;
    }
    
    ifstream infile(filename);    

    if (!infile)                
    {
        return false;
        
    }

    string name;

    while(getline(infile, name)){

        string email;
        getline(infile, email);

        int j;
        infile >> j;

        infile.ignore(10000, '\n');
        vector<string> watch_history;
        string id;


        for(int i = 0; i < j; i++){
            getline(infile, id);
            watch_history.push_back(id);
        }

        string foo;
        getline(infile, foo);
        
        User* newuser = new User(name, email, watch_history);
        m_vectorUsers.push_back(newuser);
        m_userTree.insert(email, newuser);

    }
    
    m_loaded = true;
    return true;  
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User*>::Iterator it = m_userTree.find(email);
    
    return it.get_value();
}

UserDatabase::~UserDatabase(){
    for(int i = 0; i < m_vectorUsers.size(); i++)
    {
        delete m_vectorUsers[i];
    }
}