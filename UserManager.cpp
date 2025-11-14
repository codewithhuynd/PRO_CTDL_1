//#include "UserManager.h"
//#include <conio.h>
//#include <windows.h>
//#include<cstdio>
//#include <fstream>
//#include"User.h"
//#include"AdminManager.h"
//#include"MyUnorderedMap.h"
//#include"Constants.h"
//
//
//using namespace std;
//string readPass()
//{
//    string pass;
//    char ch;
//
//    while (true)
//    {
//        ch = _getch();
//
//        if (ch == 13)
//        {
//            cout << endl;
//            break;
//        }
//        else if (ch == 8)
//        {
//            if (!pass.empty())
//            {
//                pass.pop_back();
//                cout << "\b \b";
//            }
//        }
//        else
//        {
//            pass.push_back(ch);
//            cout << '*';
//        }
//    }
//    return pass;
//}
//
//UserManager::UserManager()
//{
//}
//
//bool UserManager::loadUserData()
//{
//    ifstream ifFile("THETU_FILE_NAME");
//
//    if (!ifFile.is_open())
//    {
//        return false;
//    }
//
//    try
//    {
//        string strID, strPin;
//        while (ifFile >> strID >> strPin)
//        {
//            // Mở file id.txt để lấy thêm thông tin
//            string filename = strID + ".txt";
//            ifstream infoFile(filename);
//
//            string tenTaiKhoan = "";
//            long long soDu = 0.0;
//            string loaiTienTe = "VND";
//
//            if (infoFile.is_open())
//            {
//                string line;
//                // Đọc 4 dòng: id, tên tài khoản, số dư, loại tiền tệ
//                getline(infoFile, line); // dòng 1: id (bỏ qua)
//                getline(infoFile, tenTaiKhoan);
//                getline(infoFile, line);
//                try {
//                    soDu = stod(line);
//                }
//                catch (...) {
//                    soDu = 0.0;
//                }
//                getline(infoFile, loaiTienTe);
//                infoFile.close();
//            }
//
//            // Tạo đối tượng UserAccount với dữ liệu đầy đủ
//            UserAccount newUser(strID, strPin, tenTaiKhoan, soDu, loaiTienTe, false, true);
//
//            // Thêm vào danh sách
//            this->_listUser.insert(strID, newUser);
//        }
//    }
//    catch (...)
//    {
//        ifFile.close();
//        return false;
//    }
//
//    ifFile.close();
//    return true;
//}
//
//
//
//
//
//
//bool UserManager::loginUser()
//{
//    if (this->_listUser.empty())
//    {
//        cout << "Loi: Khong co du lieu User. Vui long kiem tra file THETU_FILE_NAME" << endl;
//        return false;
//    }
//
//    // Đếm lần nhập sai theo từng ID (không dùng biến chung)
//    
//
//    while (true)
//    {
//        string strInputID;
//        string strInputPin;
//
//        // Bật chế độ hiển thị màu ANSI cho console Windows
//        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//        DWORD dwMode = 0;
//        GetConsoleMode(hOut, &dwMode);
//        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//        SetConsoleMode(hOut, dwMode);
//
//        // Màu xanh nước biển (cyan)
//        cout << "\033[34;1m";
//        cout << "\n\n";
//
//        cout << "===================================================================\n";
//        cout << "|.__                .__                                           |\n";
//        cout << "||  |   ____   ____ |__| ____    __ __  ______ ___________        |\n";
//        cout << "||  |  /  _ \\ / ___\\|  |/    \\  |  |  \\/  ___// __ \\_  __ \\       |\n";
//        cout << "||  |_(  <_> ) /_/  >  |   |  \\ |  |  /\\___ \\\\  ___/|  | \\/       |\n";
//        cout << "||____/\\____/\\___  /|__|___|  / |____//____  >\\___  >__|          |\n";
//        cout << "|           /_____/         \\/             \\/     \\/              |\n";
//        cout << "===================================================================\n";
//        
//
//        cout << "\033[0m";
//
//        cout << "| ID: ";
//        cin >> strInputID;
//        cout << "|                                                                   |\n";
//        cout << "=====================================================================\n";
//
//        cout << "| Pin: ";
//        strInputPin = readPass();
//        cout << "|                                                                   |\n";
//        cout << "=====================================================================\n";
//
//        // Tìm user
//        auto p = _listUser.find(strInputID);
//
//        if (p == nullptr)
//        {
//            cout << "Loi: Khong tim thay tai khoan co ID = " << strInputID << "\n";
//        }
//        else if (p->isLocked())
//        {
//            cout << "Loi: Tai khoan bi khoa. Vui long lien he admin de mo khoa.\n";
//        }
//        else
//        {
//            // User tồn tại và chưa bị khóa
//            if (p->getPin() == strInputPin)
//            {
//                
//                // Thành công -> reset counter (nếu có) và trả true
//                failedAttempts.erase(strInputID);
//                cout << "=====================================================================\n";
//                cout << "|                      DANG NHAP USER THANH CONG                    |\n";
//                cout << "=====================================================================\n";
//                
//                // TODO: nếu cần, cập nhật trạng thái first-login -> false: p->setFirstLogin(false);
//                // TODO: nếu cần ghi thay đổi ra file: saveUserData();
//                runUserMenu(strInputID);
//                return true;
//            }
//            else
//            {
//                // Sai PIN
//                int* cntPtr = failedAttempts.find(strInputID);
//                if (cntPtr == nullptr) {
//                    failedAttempts.insert(strInputID, 1);
//                    cntPtr = failedAttempts.find(strInputID);
//                }
//                else {
//                    ++(*cntPtr);
//                }
//
//                int attempts = *cntPtr;
//                int remaining = 3 - attempts;
//                if (remaining > 0)
//                {
//                    cout << "Sai PIN. Con " << remaining << " lan thu viec dang nhap truoc khi khoa tai khoan.\n";
//                }
//                else
//                {
//                    // Khóa tài khoản
//                    p->setLocked(true);
//                    // TODO: persist thay đổi vào file (ví dụ gọi saveUserData() hoặc update file THETU_FILE_NAME)
//                    cout << "Tai khoan da bi khoa do nhap sai PIN qua so lan cho phep.\n";
//                }
//            }
//        }
//
//        // Nếu tới đây là fail -> hỏi người dùng có muốn thử lại (giữ logic của bạn)
//        cout << "=====================================================================\n";
//        cout << "|                   [DANG NHAP THAT BAI]                             |\n";
//        cout << "| NHAP [1] DE DANG NHAP LAI                                          |\n";
//        cout << "| NHAP [KY TU BAT KY] DE THOAT                                       |\n";
//        cout << "=====================================================================\n";
//        cout << "| NHAP TAI DAY: ";
//        char cChoice;
//        cin >> cChoice;
//        cout << "|                                                                   |\n";
//        cout << "=====================================================================\n";
//
//        if (cChoice != '1') return false;
//
//        // nếu chọn 1 -> vòng lặp tiếp, người dùng có thể nhập lại
//    } // end while
//}
//
//void UserManager::unlockUserById(const string& id)
//{
//    auto p = _listUser.find(id);
//    p->setLocked(false);
//}
//bool UserManager::isLocked(const string& id) {
//    auto p = _listUser.find(id);
//    return p->isLocked();
//}
//
//void UserManager::resetTimesLoginByID(const string& id) {
//    auto p = failedAttempts.find(id);
//    *p = 0;
//}
//
//void UserManager::displayUserMenu() {
//    cout << "\n* * * * * * * * * * * * * * * * * * * * *" << endl;
//    cout << "*             MENU USER                *" << endl;
//    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
//
//    cout << "a. Xem thong tin tai khoan" << endl;
//    cout << "b. Rut tien" << endl;
//    cout << "c. Chuyen tien" << endl;
//    cout << "d. Xem noi dung giao dich" << endl;
//
//    cout << "e. Doi ma pin" << endl;
//    cout << "f. Thoat" << endl;
//
//    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
//    cout << "Vui long chon chuc nang (a/b/c/d/e/f): ";
//}
//
//void UserManager::runUserMenu(const string& id)
//{
//    // Cần có vòng lặp để Admin có thể thực hiện nhiều chức năng cho đến khi thoát [6]
//    while (true)
//    {
//        // Hàm này sẽ in ra menu (ví dụ: 1. Xem TK, 2. Thêm TK, ...)
//        displayUserMenu();
//
//        // Khai báo và khởi tạo biến để tránh bug "phong thủy" (Debug chạy, Release không chạy) [18, 19]
//        // Sử dụng Hungarian Notation cho biến local: int iChoice [10, 11]
//        char iChoice = 0;
//
//        cout << "Vui long nhap lua chon: ";
//        // Xử lý đầu vào (đảm bảo rằng biến được khai báo gần nơi sử dụng [20])
//        cin >> iChoice;
//
//        // Dùng switch cho lựa chọn menu [8]
//        switch (iChoice)
//        {
//        case 'a': // Chức năng a. Xem danh sách Tài khoản [4]
//            loadUserData();
//            displayInforUser(id); // Tên method dùng Camel-case [10]
//            break;
//
//        case 'b': // Chức năng b. Thêm Tài Khoản [4]
//            loadUserData();
//            rutTien(id);
//            break;
//
//        case 'c': 
//            loadUserData();
//            chuyenTien(id);
//            break;
//
//        case 'd': // Chức năng d. Mở khóa Tài Khoản [5]
//            loadUserData();
//            inLichSu(id);
//            break;
//
//        case 'e': // Chức năng Thoát
//            loadUserData();
//            doiMaPin(id);
//            break;
//
//            // Cần xử lý trường hợp default trong switch case [17]
//        default:
//            // Thông báo lỗi theo yêu cầu [21]
//            cout << "Lua chon khong hop le. Vui long chon lai chuc nang (1-5).\n";
//            break;
//        }
//    }
//}
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