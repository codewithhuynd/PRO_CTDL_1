#include <iostream>
#include<windows.h>
#include "AdminManager.h"
#include"UserManager.h"
#include"DataRepository.h"
#include"ATMView.h"

using namespace std;

int main()
{
    DataRepository mainData;
    if (!mainData.loadAdminData()) {
        cout << "Khong the tai du lieu Admin!";
        return 0;
    }
    if (!mainData.loadUserData()) {
        cout << "Khong the tai du lieu User!";
        return 0;
    }

    ATMView mainView;
    AdminManager mainAdminController;

    string strChoice = mainView.displayMainMenu();
    if (strChoice == "1") {
        if (mainAdminController.loginAdmin(mainData.getAdminList())) {
            mainAdminController.runAdminMenu(mainData);
        }
    }
    

    return 0;
}