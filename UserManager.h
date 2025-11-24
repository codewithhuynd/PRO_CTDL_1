#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector> 
#include "User.h" 
#include"MyUnorderedMap.h"
#include"DataRepository.h"
#include <iostream>

using namespace std;

const int MIN_WITHDRAWAL_AMOUNT = 50000;
const int MIN_REMAINING_BALANCE = 50000;

// Tên Class sử dụng Pascal-case [7]
class UserManager
{
public:

    UserManager();
    void runUserMenu(DataRepository& mainData,const UserAccount& currentUser);
    UserAccount* loginUser(DataRepository& mainData);
    bool withdrawMoney(DataRepository& mainData, const UserAccount& currentUser);
    bool changePin(DataRepository& mainData, const UserAccount& currentUser);

};

#endif // USERMANAGER_H