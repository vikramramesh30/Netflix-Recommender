#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include "treemm.h"
#include <vector>


class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:

    TreeMultimap<std::string, User*> m_userTree;
    std::vector<User*> m_vectorUsers;
    bool m_loaded;
    
};

#endif