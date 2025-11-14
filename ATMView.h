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

class ATMView {
public:
    UserAccount displayAddUserFrame();
    void enableANSIColors();

    string displayMainMenu(); 

    Admin displayAdminLoginFrame();

    UserAccount displayUserLoginForm(); 

    int displayAdminMenu(); 

    void displayUserMenu(); 

    string readPassword();

    void displayCardList(const MyUnorderedMap<std::string, UserAccount>& listUsers); 

    void displayUserInfo(const UserAccount& user); 

    void displayTransactionHistory(const std::string& id); 

    string loginAdminFailFrame();
    string addUserFailFrame();
    string deleteAccountUserFailFrame();
    string deleteAccountUserFrame();
    string unlockAccountUserFrame();

};

#endif // ATM_VIEW_H