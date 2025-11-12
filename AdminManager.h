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
    bool loginAdmin();
    void runAdminMenu();
    void themTaiKhoan();
    

    

private:
    /*vector<Admin> _listAdmins;  */
    MyUnorderedMap<string,Admin> _listAdmins;
    MyUnorderedMap<string, TheTu> _listTheTu;
};

#endif 
