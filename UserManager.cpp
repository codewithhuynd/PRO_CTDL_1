#include "UserManager.h"
#include <conio.h>
#include <windows.h>
#include<cstdio>
#include <fstream>
#include"User.h"
#include"AdminManager.h"
#include"MyUnorderedMap.h"

UserManager::UserManager(){}

UserAccount* UserManager::loginUser(DataRepository& mainData)
{
    ATMView atmview;
   
    MyUnorderedMap<std::string, UserAccount> listUsers = mainData.getUserList();
    UserAccount loginUserInput;

    while (true) {
        loginUserInput = atmview.displayUserLoginForm(); 

        UserAccount* userPtr = listUsers.find(loginUserInput.getID());

        if (userPtr == nullptr) { 
            string choice = atmview.loginUserFailFrame();
            if (choice == "1") continue; 
            else return nullptr;
        }

        UserAccount& realUser = *userPtr;

        
        if (realUser.isLocked()) { 
            atmview.displayUserLoginForm();
            return nullptr;
        }

        
        if (realUser.getPin() != loginUserInput.getPin()) {
            realUser.increaseFailCount();

            if (realUser.getFailCount()>=3) { 
                realUser.setLocked(true); 

                MyUnorderedMap<string,UserAccount> listUserLock = mainData.getUserListLock();
                listUserLock.insert(realUser.getID(), realUser); 
                mainData.setUserListLock(listUserLock);
                mainData.setUserList(listUsers);

                std::ofstream idFile(realUser.getID() + ".txt");
                if (!idFile) {
                    return nullptr;
                }
                idFile << realUser.getID() << "\n";
                idFile << realUser.getAccountName() << "\n";
                idFile << realUser.getBalance() << "\n";
                idFile << realUser.getCurrency() << "\n";
                idFile << "BI KHOA" << "\n";
                idFile.close();

                atmview.accountLocked();
                return nullptr;
            }

            string choice = atmview.loginUserFailFrame(); 
            if (choice == "1") continue; 
            else return nullptr;
        }

        
        realUser.setFailCount(0);
        mainData.setUserList(listUsers);

        if (realUser.getPin() == DEFAULT_PIN) {
            changePin(mainData, realUser);
        }

        // 5. Xử lý Đăng nhập lần đầu (Yêu cầu phải đổi mã pin) [1]
        // Vì yêu cầu phải đổi PIN ngay trước khi vào menu chính, logic này cần được thêm vào.
        // Tuy nhiên, do không có implementation của hàm đổi PIN tại đây, 
        // ta sẽ dựa vào `isFirstLogin()` [11] để caller (main) xử lý.

        // Nếu user đã vượt qua tất cả các kiểm tra:
        return &realUser; // Trả về con trỏ tới UserAccount đã đăng nhập
    }
}
bool UserManager::changePin(DataRepository& mainData, const UserAccount& currentUser) {
    ATMView atmview;
    bool inputCorect = false;
    vector<string> input;
    while (!inputCorect) {
        input = atmview.changePinAccountUserFrame();

        if (currentUser.getPin()!=input[0]||input[1]!=input[2]||!Validation::isValidPin(input[1]))
        {
            string strChoice = atmview.changePinUserFailFrame();
            if (strChoice == "1")
                continue;
            else
                return false;
        }
        inputCorect = true;
    }

    MyUnorderedMap<string, UserAccount>listUser = mainData.getUserList();
    auto crUser = listUser.find(currentUser.getID());
    crUser->setPin(input[1]);
    mainData.setUserList(listUser);

    ofstream fout(CARD_LIST_FILE_NAME, ios::trunc);
    if (!fout) {
        return false;
    }
    listUser.for_each([&](const string& id, const UserAccount& user) {
        fout << id << " " << user.getPin() << '\n';
        });
    fout.close();
    return true;
}
bool UserManager::withdrawMoney(DataRepository& mainData,const UserAccount& currentUser) {
    ATMView atmview;
    bool inputCorect = false;
    long long llSoTienRut;
    while (!inputCorect) {
        llSoTienRut = atmview.withdrawMoneyFrame();

        if (llSoTienRut< MIN_WITHDRAWAL_AMOUNT || llSoTienRut>currentUser.getBalance()- MIN_REMAINING_BALANCE || llSoTienRut% MIN_WITHDRAWAL_AMOUNT!=0)
        {
            string strChoice = atmview.withdrawUserFailFrame();
            if (strChoice == "1")
                continue;
            else
                return false;
        }
        inputCorect = true;
    }

    MyUnorderedMap<string, UserAccount> listUser = mainData.getUserList();
    auto crUser = listUser.find(currentUser.getID());
    long long newbalance = currentUser.getBalance() - llSoTienRut;
    crUser->setBalance(newbalance);
    mainData.setUserList(listUser);

    time_t now = time(0);
    std::tm localTime;
    localtime_s(&localTime, &now);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S %d-%m-%Y", &localTime);

    std::string filename = "LichSu"+crUser->getID()+".txt";
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << crUser->getID()<<": RUT TIEN "<<llSoTienRut<<" VND, vao luc "<<buffer << "\n";
        file.close();             
    }
    else {
        return false;
    }

    std::ofstream idFile(crUser->getID() + ".txt"); 
    if (!idFile) {
        return false;
    }
    idFile << crUser->getID() << "\n";
    idFile << crUser->getAccountName() << "\n";
    idFile << crUser->getBalance() << "\n";
    idFile << crUser->getCurrency() << "\n";
    if (!crUser->isLocked()) { 
        idFile << "KHONG BI KHOA" << "\n";
    }
    else {
        idFile << "BI KHOA" << "\n";
    }
    idFile.close();

    atmview.withdrawSuccessFrame();
    return true;

}

void UserManager::runUserMenu(DataRepository& mainData,const UserAccount& currentUser)
{
    ATMView atmview;

    while (true)
    {
        int iChoice = atmview.displayUserMenu();

        switch (iChoice)
        {
        case 1:
            atmview.displayUserInfo(currentUser);
            break;

        case 2:
            withdrawMoney(mainData,currentUser);
            break;
        /*case 3:
            deleteAccountUser(mainData);
            break;

        case 4:
            unlockAccountUser(mainData);
            break;*/

        case 5:
            return;

            // Cần xử lý trường hợp default trong switch case [17]
        default:
            // Thông báo lỗi theo yêu cầu [21]
            cout << "Lua chon khong hop le. Vui long chon lai chuc nang (1-5).\n";
            break;
        }
    }
}
//
//void UserManager::displayInforUser(const string& id) {
//    string filename = id + ".txt";
//    ifstream fin(filename);
//
//    if (!fin.is_open()) {
//        cout << "Khong the mo file " << filename << endl;
//        return;
//    }
//
//    string idFile, tenTK, soDu, loaiTien;
//
//    // Đọc lần lượt 4 dòng
//    getline(fin, idFile);
//    getline(fin, tenTK);
//    getline(fin, soDu);
//    getline(fin, loaiTien);
//
//    fin.close();
//
//    cout << "===== THONG TIN TAI KHOAN =====\n";
//    cout << "ID: " << idFile << endl;
//    cout << "Ten tai khoan: " << tenTK << endl;
//    cout << "So du: " << soDu << endl;
//    cout << "Loai tien te: " << loaiTien << endl;
//}
//
//void UserManager::rutTien(const string& id) {
//    long long soTienRut;
//    bool nhapDung = false;
//    auto p = _listUser.find(id);
//    while (!nhapDung) {
//        cout << "Nhap so tien can rut: ";
//        
//        cin >> soTienRut;
//
//        if (soTienRut < MIN_WITHDRAWAL_AMOUNT)
//        {
//            cout << "\nSo tien can rut phai lon hon hoac bang 50.000 VND\n";
//            continue;
//        }
//
//        // Ràng buộc B: Số tiền cần rút phải là bội số của 50 ngàn [7]
//        if (soTienRut % MIN_WITHDRAWAL_AMOUNT != 0)
//        {
//            cout << "\nSo tien can rut phai la boi so cua 50.000";
//            // Thông báo lỗi: Xuất hiện lại giao diện nhập tiền cần rút [7]
//            continue;
//        }
//
//        // Ràng buộc C: Số dư phải giữ lại tối thiểu 50 ngàn [7]
//        // iCurrentBalance < (số tiền rút + số dư tối thiểu phải giữ)
//        if (p->getBalance() < (soTienRut + MIN_REMAINING_BALANCE))
//        {
//            cout << "\nKhong du tien, so du phai giu lai toi thieu 50.000";
//            continue;
//        }
//        nhapDung = true;
//    }
//    long long newBalance = p->getBalance()-soTienRut;
//    p->setBalance(newBalance);
//
//    // Ghi file tài khoản
//    string accFilename = id + ".txt";
//    ofstream foutAcc(accFilename, ios::trunc);
//    if (!foutAcc.is_open()) {
//        cerr << "Khong the mo file " << accFilename << " de cap nhat!\n";
//        return;
//    }
//    foutAcc << id << '\n';
//    foutAcc << p->getAccountName() << '\n';
//    foutAcc <<  p->getBalance() << '\n';
//    foutAcc << p->getCurrency() << '\n';
//    foutAcc.close();
//
//    // Ghi lịch sử giao dịch
//    string logFilename = "LichSu" + id + ".txt";
//    ofstream foutLog(logFilename, ios::app);
//    if (!foutLog.is_open()) {
//        cerr << "Khong the mo file " << logFilename << " de ghi lich su!\n";
//        return;
//    }
//
//    // Lấy thời gian hiện tại
//    time_t now = time(0);
//    tm localTime;
//    localtime_s(&localTime, &now);
//    char timeStr[30];
//    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);
//
//    // Ghi thông tin vào file lịch sử
//    foutLog << id << ": Rut Tien " << soTienRut << " VND, vao luc " << timeStr << '\n';
//    foutLog.close();
//
//    cout << "Rut tien thanh cong. So du con lai: " <<  newBalance << '\n';
//    
//}
//    
//void UserManager::chuyenTien(const string& id) {
//    string taiKhoanNhan;
//    long long soTienChuyen;
//    bool xacThucTaiKhoanNhan = false;
//    bool xacThucSoTien = false;
//
//    while (!xacThucTaiKhoanNhan) {
//        cout << "Nhap ID tai khoan nhan tien: ";
//        cin >> taiKhoanNhan;
//        auto p = _listUser.find(taiKhoanNhan);
//        if (p == nullptr) {
//            cout << "\nKhong tim thay tai khoan\n";
//            continue;
//        }
//        else xacThucTaiKhoanNhan = true;
//    }
//
//    while (!xacThucSoTien) {
//        cout << "Nhap so tien can rut: ";
//
//        cin >> soTienChuyen;
//
//        if (soTienChuyen < MIN_WITHDRAWAL_AMOUNT)
//        {
//            cout << "\nSo tien chuyen phai lon hon hoac bang 50.000 VND\n";
//            continue;
//        }
//
//        // Ràng buộc B: Số tiền cần rút phải là bội số của 50 ngàn [7]
//        if (soTienChuyen % MIN_WITHDRAWAL_AMOUNT != 0)
//        {
//            cout << "\nSo tien chuyen phai la boi so cua 50.000";
//            // Thông báo lỗi: Xuất hiện lại giao diện nhập tiền cần rút [7]
//            continue;
//        }
//        auto a = _listUser.find(id);
//        // Ràng buộc C: Số dư phải giữ lại tối thiểu 50 ngàn [7]
//        // iCurrentBalance < (số tiền rút + số dư tối thiểu phải giữ)
//        if (a->getBalance() < (soTienChuyen + MIN_REMAINING_BALANCE))
//        {
//            cout << "\nKhong du tien, so du phai giu lai toi thieu 50.000";
//            continue;
//        }
//        xacThucSoTien = true;
//    }
//    auto c = _listUser.find(id);
//    auto b = _listUser.find(taiKhoanNhan);
//    long long newBalance = b->getBalance() + soTienChuyen;
//    b->setBalance(newBalance);
//    string accFilename = taiKhoanNhan + ".txt";
//    ofstream foutAcc(accFilename, ios::trunc);
//    if (!foutAcc.is_open()) {
//        cerr << "Khong the mo file " << accFilename << " de cap nhat!\n";
//        return;
//    }
//    foutAcc << taiKhoanNhan << '\n';
//    foutAcc << b->getAccountName() << '\n';
//    foutAcc << b->getBalance() << '\n';
//    foutAcc << b->getCurrency() << '\n';
//    foutAcc.close();
//
//    string logFilenamee = "LichSu" + taiKhoanNhan + ".txt";
//    ofstream foutLogg(logFilenamee, ios::app);
//    if (!foutLogg.is_open()) {
//        cerr << "Khong the mo file " << logFilenamee << " de ghi lich su!\n";
//        return;
//    }
//
//    // Lấy thời gian hiện tại
//    time_t now = time(0);
//    tm localTime;
//    localtime_s(&localTime, &now);
//    char timeStr[30];
//    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);
//
//    // Ghi thông tin vào file lịch sử
//    foutLogg << "Nhan tien tu " << id << " " << c->getAccountName() << " " << soTienChuyen << " VND, vao luc " << timeStr << '\n';
//    foutLogg.close();
//
//    
//    long long newBalance2 = c->getBalance() - soTienChuyen;
//    c->setBalance(newBalance2);
//    string acccFilename = id + ".txt";
//    ofstream foutAccc(acccFilename, ios::trunc);
//    if (!foutAccc.is_open()) {
//        cerr << "Khong the mo file " << acccFilename << " de cap nhat!\n";
//        return;
//    }
//    foutAccc << id << '\n';
//    foutAccc << c->getAccountName() << '\n';
//    foutAccc << c->getBalance() << '\n';
//    foutAccc << c->getCurrency() << '\n';
//    foutAccc.close();
//
//    string logFilename = "LichSu" + id + ".txt";
//    ofstream foutLog(logFilename, ios::app);
//    if (!foutLog.is_open()) {
//        cerr << "Khong the mo file " << logFilename << " de ghi lich su!\n";
//        return;
//    }
//
//    // Lấy thời gian hiện tại
//  /*  time_t now = time(0);
//    tm localTime;
//    localtime_s(&localTime, &now);
//    char timeStr[30];
//    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);*/
//
//    // Ghi thông tin vào file lịch sử
//    foutLog << "Chuyen tien " << taiKhoanNhan << " " <<b->getAccountName()<<" "<<soTienChuyen<< " VND, vao luc " << timeStr << '\n';
//    foutLog.close();
//
//    cout << "Chuyen tien thanh cong. So du con lai: " << newBalance2 << '\n';
//}
//
////void UserManager::doiMaPin(const string& id) {
////    bool pinHienTai = false;
////    bool pinMoi = false;
////    bool xacNhan = false;
////    string pinHT;
////    string pinM;
////    string pinXN;
////    auto a = _listUser.find(id);
////    while (!pinHienTai&&!pinMoi&&!xacNhan) {
////        cout << "Nhap ma pin hien tai: ";
////        cin >> pinHT;
////        if (a->getPin() == pinHT) {
////            pinHienTai = true;
////        }
////
////        cout << "\nNhap ma pin moi: ";
////        cin >> pinM;
////        if (pinM.size() == 6) {
////            pinMoi = true;
////        }
////
////        cout << "\nXac thuc lai ma pin moi: ";
////        cin >> pinXN;
////        if (pinM == pinXN) {
////            xacNhan = true;
////        }
////
////        if (!pinHienTai) cout << "\nNhap sai ma pin hien tai, vui long nhap lai!";
////        if (!pinMoi) cout << "\nMa pin moi bao gom 6 chu so, vui long nhap lai!";
////        if (!xacNhan) cout << "\nNhap sai ma pin xac thuc, vui long nhap lai!";
////    }
////
////    a->setPin(pinM);
////    AdminManager admin;
////    admin.capNhatMaPinByID(id, pinM);
////    cout << "\nMa pin da duoc cap nhat thanh cong";
////
////}
//
//void UserManager::inLichSu(const string& id) {
//    string fileName = "LichSu" + id + ".txt";
//    ifstream file(fileName);
//
//    if (!file.is_open()) {
//        cout << "Khong tim thay file lich su cho ID " << id << endl;
//        return;
//    }
//
//    cout << "===== LICH SU GIAO DICH CUA ID: " << id << " =====" << endl;
//
//    string line;
//    int count = 1;
//    while (getline(file, line)) {
//        cout << count++ << ". " << line << endl;
//    }
//
//    if (count == 1)
//        cout << "(Khong co giao dich nao duoc luu)\n";
//
//    file.close();
//}
//
//static bool isAllDigits(const string& s) {
//    if (s.empty()) return false;
//    for (char c : s) if (!isdigit(static_cast<unsigned char>(c))) return false;
//    return true;
//}
//
//void UserManager::doiMaPin(const string& id) {
//    auto a = _listUser.find(id);
//    if (!a) {
//        cout << "Khong tim thay user co ID = " << id << "\n";
//        return;
//    }
//
//    bool pinHienTai = false;
//    bool pinMoi = false;
//    bool xacNhan = false;
//    string pinHT, pinM, pinXN;
//
//    // Lặp đến khi cả 3 điều kiện đều thỏa
//    while (!pinHienTai || !pinMoi || !xacNhan) {
//        // Nhập và kiểm tra PIN hiện tại
//        cout << "Nhap ma pin hien tai: ";
//        pinHT = readPass();
//        if (a->getPin() == pinHT) {
//            pinHienTai = true;
//        }
//        else {
//            pinHienTai = false;
//            cout << "Nhap sai ma pin hien tai, vui long nhap lai!\n";
//            // tiếp vòng để nhập lại; không cần hỏi PIN mới nếu hiện tại sai
//            continue;
//        }
//
//        // Nhập PIN mới
//        cout << "Nhap ma pin moi (6 chu so): ";
//        pinM = readPass();
//        if (pinM.size() == 6 && isAllDigits(pinM)) {
//            pinMoi = true;
//        }
//        else {
//            pinMoi = false;
//            cout << "Ma pin moi phai gom 6 chu so, vui long nhap lai!\n";
//            continue;
//        }
//
//        // Xác nhận
//        cout << "Xac thuc lai ma pin moi: ";
//        pinXN = readPass();
//        if (pinM == pinXN) {
//            xacNhan = true;
//        }
//        else {
//            xacNhan = false;
//            cout << "Nhap sai ma pin xac thuc, vui long nhap lai!\n";
//            // quay lại nhập PIN mới
//        }
//    }
//
//    // Tại đây: đã thỏa cả 3 điều kiện
//    a->setPin(pinM);
//    AdminManager admin;
//    // Cập nhật persistent storage: dùng admin được truyền vào (đảm bảo đã load dữ liệu)
//    if (!admin.capNhatMaPinByID(id, pinM)) {
//        cout << "Cap nhat PIN vao file that bai!\n";
//    }
//    else {
//        cout << "Ma pin da duoc cap nhat thanh cong\n";
//    }
//}