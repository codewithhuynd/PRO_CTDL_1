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
    cout << "\033[34;1m";
    cout << "           ____________________________________\n";
    cout << "          /_____/_____/_____/_____/_____/_____/\n";
    cout << "          |_|     \033[36;1mCHON CHE DO DANG NHAP\033[34;1m     |_|\n";
    cout << "          -------------------------------------\n";
    cout << "          /_____/_____/_____/_____/_____/_____/\n";
    cout << "\033[36;1m        [1] DANG NHAP ADMIN     [2] DANG NHAP USER\033[0m\n";

    string cChoice;
    cin >> cChoice;
    return cChoice;
}

Admin ATMView::displayAdminLoginFrame() {
    enableANSIColors();
    cout << "\033[34;1m";
    cout << "\n\n";


    cout << "===========================================================\n";
    cout << "|\033[36;1m  _             _                   _           _        \033[34;1m|\n";
    cout << "|\033[36;1m | |           (_)                 | |         (_)       \033[34;1m|\n";
    cout << "|\033[36;1m | | ___   __ _ _ _ __     __ _  __| |_ __ ___  _ _ __   \033[34;1m|\n";
    cout << "|\033[36;1m | |/ _ \\ / _` | | '_ \\   / _` |/ _` | '_ ` _ \\| | '_ \\  \033[34;1m|\n";
    cout << "|\033[36;1m | | (_) | (_| | | | | | | (_| | (_| | | | | | | | | | | \033[34;1m|\n";
    cout << "|\033[36;1m |_|\\___/ \\__, |_|_| |_|  \\__,_|\\__,_|_| |_| |_|_|_| |_| \033[34;1m|\n";
    cout << "|\033[36;1m           __/ |                                         \033[34;1m|\n";
    cout << "|\033[36;1m          |___/                                          \033[34;1m|\n";
    cout << "===========================================================\n";
    cout << "\033[97;1m";
    string strUser;
    cout << "  USER: \033[0m";
    cin >> strUser;

    string strPass;
    cout << "\033[97;1m  PASS: \033[0m";
    strPass = readPassword();
    cout << "\n";
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

int ATMView::displayAdminMenu() {
    enableANSIColors();
    cout << "\033[34;1m";
    cout << "===========================================================" << endl;
    cout << "========================\033[97;1m MENU ADMIN\033[34;1m =======================" << endl;
    cout << "|\033[36;1m         1. Xem danh sach Tai khoan                     \033[34;1m |" << endl;
    cout << "|\033[36;1m         2. Them Tai Khoan                              \033[34;1m |" << endl;
    cout << "|\033[36;1m         3. Xoa The                                     \033[34;1m |" << endl;
    cout << "|\033[36;1m         4. Mo khoa Tai Khoan                           \033[34;1m |" << endl;
    cout << "|\033[36;1m         5. Thoat chuong trinh/Dang xuat                \033[34;1m |" << endl;
    cout << "===========================================================" << endl;
    cout << "\033[36;1m";

    int iChoice;
    cin >> iChoice;
    return iChoice;

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
        << "\n=================== "
        << "\033[36;1m"
        << "DANH SACH TAI KHOAN"
        << "\033[32;1m"
        << " ===================" << endl;

    cout << "\033[97m";
    listUsers.for_each([&](const string& id, const UserAccount& user) {
        cout << "\033[90mID:            \033[0m" << id << "\n";
        cout << "\033[90mTen tai khoan: \033[0m" << user.getAccountName() << "\n";
        cout << "\033[90mSo du :        \033[0m" << user.getBalance() << "\n";
        cout << "\033[90mLoai tien te:  \033[0m" << user.getCurrency() << "\n";
        cout << "\033[93m===========================================================\n\033[0m";
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

string ATMView::loginAdminFailFrame() {
    enableANSIColors();

    cout << "\033[38;5;45m";
    cout << "===========================================================\n";

    cout << "|\033[91m          Ten dang nhap hoac mat khau khong dung         \033[38;5;45m|\n";
    cout << "|\033[96;1m   Nhap [1] de dang nhap lai, nhap phim bat ki de thoat  \033[38;5;45m|\n";

    cout << "\033[38;5;45m";
    cout << "===========================================================\n";

    cout << "\033[0m";

    string strChoice;
    cin >> strChoice;
    return strChoice;
}
string ATMView::addUserFailFrame() {
    enableANSIColors();

    cout << "\033[38;5;45m";
    cout << "===========================================================\n";

    cout << "|\033[91m ID, Ten tai khoan, So du hoac Loai tien te khong hop le \033[38;5;45m|\n";
    cout << "|\033[96;1m   Nhap [1] de dang nhap lai, nhap phim bat ki de thoat  \033[38;5;45m|\n";

    cout << "\033[38;5;45m";
    cout << "===========================================================\n";

    cout << "\033[0m\n";

    string strChoice;
    cin >> strChoice;
    return strChoice;
}

UserAccount ATMView::displayAddUserFrame() {
   
    enableANSIColors();

    
    cout << "\033[32;1m" 
        << "\n============== "
        << "\033[36;1m" 
        << "NHAP THONG TIN TAI KHOAN MOI"
        << "\033[32;1m" 
        << " ===============\n";
    cout << "\033[97;1m";

    cout << "ID:            \033[0m";
    string strID;
    cin >> strID;
    cin.ignore(); 

    cout << "\033[97;1mTen tai khoan: \033[0m";
    string strTenTaiKhoan;
    getline(cin, strTenTaiKhoan); 

    cout << "\033[97;1mSo du:         \033[0m";
    long long lSoDu;
    cin >> lSoDu;
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        return UserAccount("", "", "", 0, "", false, false);
    }

    cout << "\033[97;1mLoai tien te:  \033[0m";
    string strLoaiTienTe;
    cin >> strLoaiTienTe;

    
    cout << "\033[0m";

    UserAccount newUser(strID, DEFAULT_PIN, strTenTaiKhoan, lSoDu, strLoaiTienTe, false, true);
    return newUser;
}

string ATMView::deleteAccountUserFrame() {

    enableANSIColors();


    cout << "\033[32;1m"
        << "\n=============== "
        << "\033[36;1m"
        << "NHAP ID TAI KHOAN CAN XOA"
        << "\033[32;1m"
        << " ===============\n";
    cout << "\033[36;1m";

    cout << "ID: ";
    string strID;
    cin >> strID;
    return strID;
}

string ATMView::deleteAccountUserFailFrame() {
    enableANSIColors();

    cout << "\033[32;1m";
    cout << "=============================================================\n";

    cout << "\033[91m";
    cout << "      ID khong hop le hoac tai khoan khong ton tai           \n";

    cout << "\033[36;1m";
    cout << "     Nhap [1] de lam lai, nhap phim bat ki de thoat    \n";

    cout << "\033[32;1m";
    cout << "=============================================================\n";

    cout << "\033[0m";

    string strChoice;
    cin >> strChoice;
    return strChoice;
}

string ATMView::unlockAccountUserFrame() {
    enableANSIColors();


    cout << "\033[32;1m"
        << "\n=============== "
        << "\033[36;1m"
        << "NHAP ID TAI KHOAN CAN MO KHOA"
        << "\033[32;1m"
        << " ===============\n";
    cout << "\033[36;1m";

    cout << "ID: ";
    string strID;
    cin >> strID;
    return strID;
}
