#include <iostream>
#include<windows.h>
#include "AdminManager.h"
#include"UserManager.h"

using namespace std;
void enableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
int main()
{
    enableANSIColors();
    AdminManager adminManager;
    UserManager usermanager;
    cout << "\033[36;1m"; 
    cout << "    ____________________________________\n";
    cout << "   /_____/_____/_____/_____/_____/_____/\n";
    cout << "   |_|     \033[33;1mCHON CHE DO DANG NHAP\033[36;1m     |_|\n"; 
    cout << "   -------------------------------------\n";
    cout << "   /_____/_____/_____/_____/_____/_____/\n";
    cout << "\033[33;1m[1] DANG NHAP ADMIN      [2] DANG NHAP USER\033[0m\n";

    

    int x;
    cin >> x;
    if (x == 1) {
        if (!adminManager.loadAdminData()) {
            cout << "Khong the tai du lieu admin! Kiem tra file Admin.txt" << endl;
            return 0;
        }

        if (adminManager.loginAdmin()) {
            adminManager.runAdminMenu(); // FIX: Call runAdminMenu() as a member function of adminManager
        }
        else {
            cout << "Thoat chuong trinh!" << endl;
        }
    }
    if (x == 2) {
        if (!usermanager.loadUserData()) {
           cout << "Khong the tai du lieu admin! Kiem tra file Admin.txt" << endl;
            return 0;
        }

        if (usermanager.loginUser()) {
           /* adminManager.runAdminMenu();*/ // FIX: Call runAdminMenu() as a member function of adminManager
        }
        else {
            cout << "Thoat chuong trinh!" << endl;
        }
    }

    

    return 0;
}