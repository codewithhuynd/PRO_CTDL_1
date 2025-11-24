#ifndef ATM_VIEW_H
#define ATM_VIEW_H

#include <string>
#include <iostream>
#include <conio.h> 
#include <windows.h> 
#include"MyUnorderedMap.h"
#include"User.h"
#include"Admin.h"
#include"DataRepository.h"
#include"Validation.h"

class ATMView {
public:
    UserAccount displayAddUserFrame();
    void enableANSIColors();

    string displayMainMenu(); 

    Admin displayAdminLoginFrame();

    UserAccount displayUserLoginForm(); 

    int displayAdminMenu(); 

    int displayUserMenu(); 

    string readPassword();

    void displayCardList(const MyUnorderedMap<std::string, UserAccount>& listUsers); 

    void displayUserInfo(const UserAccount& user); 

    void displayTransactionHistory(const std::string& id); 

    string loginAdminFailFrame();
    string addUserFailFrame();
    string deleteAccountUserFailFrame();
    string deleteAccountUserFrame();
    string unlockAccountUserFrame();
    void addUserSuccessFrame();
    void deleteUserSuccessFrame();

    void displayListUsersLock(const MyUnorderedMap<std::string, UserAccount>& listUsersLock);
    void listUsersLockEmpty();
    string unlockAccountUserFailFrame();
    void unlockAccountUserSuccess();
    long long withdrawMoneyFrame();
    string withdrawUserFailFrame();
  

};

#endif // ATM_VIEW_H