#ifndef ADMIN_H_
#define ADMIN_H_

#include <string> 

class Admin
{
public:
    
    Admin() : _strUser(""), _strPass("") {}

        Admin(const std::string& strUser, const std::string& strPass)
        : _strUser(strUser), _strPass(strPass)
    {
    }

        std::string getUser() const { return _strUser; }
        std::string getPass() const { return _strPass; }

private:
    
        std::string _strUser; 
        std::string _strPass; 
};

#endif // ADMIN_H_