#ifndef ATM_VIEW_H
#define ATM_VIEW_H

#include <string>
#include <iostream>
#include <conio.h> 
#include <windows.h> 
#include"MyUnorderedMap.h"
#include"User.h"
#include"Admin.h"

class ATMView {
public:
    
    void enableANSIColors();

    string displayMainMenu(); 

    Admin displayAdminLoginFrame();

    UserAccount displayUserLoginForm(); 

    void displayAdminMenu(); 

    void displayUserMenu(); 

    string readPassword();

    void displayCardList(const MyUnorderedMap<std::string, UserAccount>& listUsers); 

    void displayUserInfo(const UserAccount& user); 

    void displayTransactionHistory(const std::string& id); 

    string loginFailFrame();

};

#endif // ATM_VIEW_H