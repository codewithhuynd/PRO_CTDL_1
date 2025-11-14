#ifndef ADMIN_MANAGER_H
#define ADMIN_MANAGER_H


#include "Admin.h"
#include <vector>
#include <fstream>
#include <iostream>
#include"MyUnorderedMap.h"
#include"TheTu.h"
#include"ATMView.h"
#include"DataRepository.h"
using namespace std;

class AdminManager
{
public:
    AdminManager();
    bool loginAdmin(const MyUnorderedMap<std::string, Admin>& admins);
    void runAdminMenu(DataRepository& mainData);
    bool addAccountUser(DataRepository& mainData);
    bool deleteAccountUser(DataRepository& mainData);
    bool unlockAccountUser(DataRepository& mainData);
    

    

private:
    DataRepository mainData;
};

#endif 
