#include "ATMView.h"
#include<fstream>
using namespace std;
void ATMView::enableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

string ATMView::displayMainMenu() {
    enableANSIColors();
    cout << "\033[32;1m";
    cout << "   ____________________________________\n";
    cout << "  /_____/_____/_____/_____/_____/_____/\n";
    cout << "  |_|   \033[36;1mCHON CHE DO DANG NHAP\033[32;1m   |_|\n";
    cout << "  -------------------------------------\n";
    cout << "  /_____/_____/_____/_____/_____/_____/\n";
    cout << "\033[36;1m[1] DANG NHAP ADMIN     [2] DANG NHAP USER\033[0m\n";

    string cChoice;
    cin >> cChoice;
    return cChoice;
}

Admin ATMView::displayAdminLoginFrame() {
    enableANSIColors();
    cout << "\033[32;1m";
    cout << "\n\n";


    cout << "=============================================================\n";
    cout << "|  _             _                   _           _          |\n";
    cout << "| | |           (_)                 | |         (_)         |\n";
    cout << "| | | ___   __ _ _ _ __     __ _  __| |_ __ ___  _ _ __     |\n";
    cout << "| | |/ _ \\ / _` | | '_ \\   / _` |/ _` | '_ ` _ \\| | '_ \\    |\n";
    cout << "| | | (_) | (_| | | | | | | (_| | (_| | | | | | | | | | |    |\n";
    cout << "| |_|\\___/ \\__, |_|_| |_|  \\__,_|\\__,_|_| |_| |_|_|_| |_|   |\n";
    cout << "|           __/ |                                           |\n";
    cout << "|          |___/                                            |\n";
    cout << "=============================================================\n";
    cout << "\033[36;1m";
    string strUser;
    cout << "USER: ";
    cin >> strUser;

    string strPass;
    cout << "\nPASS: ";
    cin >> strPass;

    Admin admin(strUser,strPass);
    return admin;

}

UserAccount ATMView::displayUserLoginForm() {
    enableANSIColors();
    cout << "\033[32;1m";
    cout << "\n\n";

    cout << "=============================================================\n";
    cout << "|.__                .__                                     |\n";
    cout << "||  |   ____   ____ |__| ____    __ __  ______ ___________  |\n";
    cout << "||  |  /  _ \\ / ___\\|  |/    \\  |  |  \\/  ___// __ \\_  __ \\ |\n";
    cout << "||  |_(  <_> ) /_/  >  |   |  \\ |  |  /\\___ \\\\  ___/|  | \\/ |\n";
    cout << "||____/\\____/\\___  /|__|___|  / |____//____  >\\___  >__|    |\n";
    cout << "|           /_____/         \\/             \\/     \\/        |\n";
    cout << "=============================================================\n";
    cout << "\033[36;1m";
    string strID;
    cout << "ID: ";
    cin >> strID;

    string strPin;
    cout << "\nPin: ";
    strPin = readPassword();

    UserAccount user(strID, strPin, "", 0, "", false, false);
    return user;
}

void ATMView::displayAdminMenu() {
    enableANSIColors();
    cout << "\033[32;1m";
    cout << "=============================================================" << endl;
    cout << "======================== MENU ADMIN =========================" << endl;
    cout << "|\033[36;1m   1. Xem danh sach Tai khoan                     \033[32;1m |" << endl;
    cout << "|\033[36;1m   2. Them Tai Khoan                              \033[32;1m |" << endl;
    cout << "|\033[36;1m   3. Xoa The                                     \033[32;1m |" << endl;
    cout << "|\033[36;1m   4. Mo khoa Tai Khoan                           \033[32;1m |" << endl;
    cout << "|\033[36;1m   5. Thoat chuong trinh/Dang xuat                \033[32;1m |" << endl;
    cout << "=============================================================" << endl;
    cout << "\033[36;1m";

}

string ATMView::readPassword()
{
    string pass;
    char ch;

    while (true)
    {
        ch = _getch();

        if (ch == 13)
        {
            cout << endl;
            break;
        }
        else if (ch == 8)
        {
            if (!pass.empty())
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            pass.push_back(ch);
            cout << '*';
        }
    }
    return pass;
}

void ATMView::displayUserMenu() {
    enableANSIColors();
    cout << "\033[32;1m";
    cout << "=============================================================" << endl;
    cout << "======================== MENU USER ==========================" << endl;
    cout << "|\033[36;1m         1. Xem thong tin tai khoan                  \033[32;1m|" << endl;
    cout << "|\033[36;1m         2. Rut tien                                 \033[32;1m|" << endl;
    cout << "|\033[36;1m         3. Chuyen tien                              \033[32;1m|" << endl;
    cout << "|\033[36;1m         4. Xem noi dung giao dich                   \033[32;1m|" << endl;
    cout << "|\033[36;1m         5. Doi ma pin                               \033[32;1m|" << endl;
    cout << "|\033[36;1m         6. Thoat                                    \033[32;1m|" << endl;
    cout << "=============================================================" << endl;
    cout << "\033[36;1m";
}

void ATMView::displayCardList(const MyUnorderedMap<std::string, UserAccount>& listUsers) {
    enableANSIColors();

    cout << "\033[32;1m"
        << "\n======================= "
        << "\033[36;1m"
        << "DANH SACH TAI KHOAN"
        << "\033[32;1m"
        << " ===================" << endl;

    cout << "\033[36;1m";
    listUsers.for_each([&](const string& id, const UserAccount& user) {
        cout << id << " " << user.getPin() << '\n';
        });
    cout << "\033[0m";
}

void ATMView::displayUserInfo(const UserAccount& user) {
    enableANSIColors();

    cout << "\033[32;1m"
        << "\n======================= "
        << "\033[36;1m"
        << "THONG TIN TAI KHOAN"
        << "\033[32;1m"
        << " =======================\n";

    cout << "\033[36;1m";
    cout << "ID: " << user.getID() << endl;
    cout << "Ten tai khoan: " << user.getAccountName() << endl;
    cout << "So du: " << user.getBalance() << endl;
    cout << "Loai tien te: " << user.getCurrency() << endl;

    cout << "\033[0m";
}

void ATMView::displayTransactionHistory(const std::string& id) {
    enableANSIColors();

    cout << "\033[32;1m"
        << "\n======================= "
        << "\033[36;1m"
        << "LICH SU GIAO DICH"
        << "\033[32;1m"
        << " =======================\n";

    string fileName = "LichSu" + id + ".txt";
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "\033[91m";
        cout << "Khong tim thay file lich su cho ID " << id << endl;
        cout << "\033[0m";
        return;
    }

    cout << "\033[36;1m";
    string line;
    int count = 1;
    while (getline(file, line)) {
        cout << count++ << ". " << line << endl;
    }

    if (count == 1) {
        cout << "\033[91m" << "Khong co giao dich nao duoc luu!\n";
    }

    file.close();

    cout << "\033[0m";
}

string ATMView::loginFailFrame() {
    enableANSIColors();

    cout << "\033[32;1m";
    cout << "=============================================================\n";

    cout << "\033[91m";
    cout << "           Ten dang nhap hoac mat khau khong dung            \n";

    cout << "\033[36;1m";
    cout << "     Nhap [1] de dang nhap lai, nhap phim bat ki de thoat    \n";

    cout << "\033[32;1m";
    cout << "=============================================================\n";

    cout << "\033[0m";

    string strChoice;
    cin >> strChoice;
    return strChoice;
}