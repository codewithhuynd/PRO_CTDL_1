#include "AdminManager.h"
#include <conio.h>
#include <windows.h>
#include<cstdio>
#include"UserManager.h"
#include"Constants.h"





AdminManager::AdminManager()
{
}

bool AdminManager::loginAdmin()
{
    ATMView atmview;
    Admin loginAdmin; 
    DataRepository repo;
    bool lgAdminSuccess = false;

    if (!repo.loadAdminData()) {
        cerr << "Loi: Khong the nap du lieu admin. Vui long kiem tra file.\n";
        return false;
    }

    while (true) {
        loginAdmin = atmview.displayAdminLoginFrame();

        Admin* adminCheck = repo.getAdmin(loginAdmin.getUser());

        if (adminCheck== nullptr || adminCheck->getPass()!=loginAdmin.getPass()) {

            string strChoice = atmview.loginFailFrame();
            if (strChoice == "1")
                continue;
            else
                return false;
        }
        lgAdminSuccess = true;
        break;
    }


}

void AdminManager::themTaiKhoan() {
    DataRepository dtrepo;
    dtrepo.loadUserData();
    string strID, strAccountName, strLoaiTienTe;
    long long soDu;

    while (true) {
        cout << "Nhap ID: ";
        cin >> strID;
        cin.ignore();

        cout << "\nNhap ten tai khoan: ";
        getline(cin, strAccountName);

        cout << "\nNhap so du: ";
        cin >> soDu;

        cout << "\nNhap loai tien te (VND,USD): ";
        cin >> strLoaiTienTe;
    }

}

void AdminManager::runAdminMenu()
{
    ATMView atmview;
    DataRepository dtrepo;
    while (true)
    {
        dtrepo.loadUserData();
        atmview.displayAdminMenu();
        char iChoice = 0;
        cin >> iChoice;

        switch (iChoice)
        {
        case '1': 
            atmview.displayCardList(dtrepo.getUserList());
            break;

        case '2': 
            addAccount();
            break;

        case 'c': // Chức năng c. Xóa Thẻ [4]
            loadTheTuData();
            deleteCard();
            break;

        case 'd': // Chức năng d. Mở khóa Tài Khoản [5]
            loadTheTuData();
            unlockAccountById();
            break;

        case 'e': // Chức năng Thoát
            cout << "Da thoat khoi menu Admin.\n";
            return; // Thoát khỏi vòng lặp và hàm menu

            // Cần xử lý trường hợp default trong switch case [17]
        default:
            // Thông báo lỗi theo yêu cầu [21]
            cout << "Lua chon khong hop le. Vui long chon lai chuc nang (1-5).\n";
            break;
        }
    }
}


