#ifndef DATA_REPOSITORY_H
#define DATA_REPOSITORY_H

#include "Admin.h"
#include "User.h" 
#include "MyUnorderedMap.h"
#include <string>
#include <fstream>
#include <ctime>
#include <iostream> 


const std::string ADMIN_FILE_NAME = "Admin.txt";
const std::string CARD_LIST_FILE_NAME = "TheTu.txt";
const std::string DEFAULT_PIN = "123456"; 

class DataRepository {
public:
    DataRepository() = default;

    bool loadAdminData(); 
    bool loadUserData(); 
    
    const MyUnorderedMap<std::string, Admin>& getAdminList() const { return _listAdmins; }
    const MyUnorderedMap<std::string, UserAccount>& getUserList() const { return _listUsers; }

    void setAdminList(const MyUnorderedMap<std::string, Admin>& admins) {
        _listAdmins = admins;
    }

    void setUserList(const MyUnorderedMap<std::string, UserAccount>& users) {
        _listUsers = users;
    }

    const MyUnorderedMap<std::string, UserAccount>& getUserListLock() const { return _listUsersLock; }
    void setUserListLock(const MyUnorderedMap<std::string, UserAccount>& usersLock) {
        _listUsersLock = usersLock;
    }

private:
    MyUnorderedMap<std::string, Admin> _listAdmins;
    MyUnorderedMap<std::string, UserAccount> _listUsers;
    MyUnorderedMap<std::string, UserAccount> _listUsersLock;

    
};

#endif