//#ifndef USERMANAGER_H
//#define USERMANAGER_H
//
//#include <string>
//#include <vector> // Dùng để quản lý danh sách Users hoặc thông tin thẻ từ
//#include "User.h" // Class UserAccount đã được định nghĩa trước đó
//#include"MyUnorderedMap.h"
//#include <iostream>
//
//using namespace std;
//
//const int MIN_WITHDRAWAL_AMOUNT = 50000;
//const int MIN_REMAINING_BALANCE = 50000;
//
//// Tên Class sử dụng Pascal-case [7]
//class UserManager
//{
//public:
//    // ---------------------- CONSTRUCTOR / DESTRUCTOR ----------------------
//
//    UserManager();
//    bool loadUserData();
//    bool loginUser();
//    void unlockUserById(const string& id);
//    bool isLocked(const string& id);
//    void resetTimesLoginByID(const string& id);
//    void displayUserMenu();
//    void runUserMenu(const string& id);
//    void displayInforUser(const string& id);
//    void rutTien(const string& id);
//    void chuyenTien(const string& id);
//    void doiMaPin(const string& id);
//    void inLichSu(const string& id);
//
//private:
//    MyUnorderedMap<string, UserAccount> _listUser;
//    MyUnorderedMap<string, int> failedAttempts;
//
//};
//
//#endif // USERMANAGER_H