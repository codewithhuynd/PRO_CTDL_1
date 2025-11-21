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
//const int MIN_WITHDRAWAL_AMOUNT = 50000; 
//const int MIN_REMAINING_BALANCE = 50000; 

class DataRepository {
public:
    DataRepository() = default;

    bool loadAdminData(); 
    bool loadUserData(); 

    /*Admin* getAdmin(const std::string& user);
    UserAccount* getUser(const std::string& id);*/

    
    const MyUnorderedMap<std::string, Admin>& getAdminList() const { return _listAdmins; }
    const MyUnorderedMap<std::string, UserAccount>& getUserList() const { return _listUsers; }

    /*bool addNewUser(const std::string& strID, const std::string& strTenTaiKhoan, const std::string& strLoaiTienTe, long long llSoDu);
    bool deleteUser(const std::string& strID);
    bool updatePin(const std::string& id, const std::string& pinMoi);*/


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