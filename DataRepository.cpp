#include "DataRepository.h"
bool DataRepository::loadAdminData()
{
    std::ifstream fin(ADMIN_FILE_NAME);

    if (!fin.is_open())
    {
        std::cerr << "Loi: Khong the mo file " << ADMIN_FILE_NAME << std::endl;
        return false; 
    }

    std::string strUser, strPass;

    while (fin >> strUser >> strPass)
    {
        Admin a(strUser, strPass);
        _listAdmins.insert(strUser, a);
    }

    fin.close();
    std::cout << "Doc file " << ADMIN_FILE_NAME << " thanh cong. Tong so admin: " << _listAdmins.size() << std::endl;
    return true; 
}

bool DataRepository::loadUserData()
{
    std::ifstream ifFile(CARD_LIST_FILE_NAME); 
    if (!ifFile.is_open())
    {
        return false;
    }

    std::string strID, strPin;
    while (ifFile >> strID >> strPin)
    {
        std::string filename = strID + ".txt"; 
        std::ifstream infoFile(filename);

        std::string strTenTaiKhoan = "";
        long long llSoDu = 0; 
        std::string strLoaiTienTe = "VND";
        bool bIsLocked = false;
        bool bIsFirstLogin = (strPin == DEFAULT_PIN);

        if (infoFile.is_open())
        {
            std::string line;

            if (std::getline(infoFile, line))
            {
            }

            if (std::getline(infoFile, strTenTaiKhoan))
            {
            }

            if (std::getline(infoFile, line))
            {
                try {
                    llSoDu = std::stoll(line);
                }
                catch (...) {
                    llSoDu = 0;
                }
            }

            if (std::getline(infoFile, strLoaiTienTe))
            {
            }

            infoFile.close(); 
        }
        else
        {
            std::cerr << "LOI: Khong the mo file " + strID + ".txt\n";
            return false;
        }

        UserAccount newUser(strID, strPin, strTenTaiKhoan, llSoDu, strLoaiTienTe, bIsLocked, bIsFirstLogin);
        this->_listUsers.insert(strID, newUser); 
    }

    ifFile.close();
    return true;
}

Admin* DataRepository::getAdmin(const std::string& user)
{
    Admin* admin = _listAdmins.find(user); 
    if (admin == nullptr) return nullptr;
    if (admin->getUser() == user)
        return admin;
    return nullptr;
}


UserAccount* DataRepository::getUser(const std::string& id)
{
    auto user = _listUsers.find(id);
    if (user->getID() == id)
        return user;
    return nullptr;
}

bool DataRepository::addNewUser(const std::string& strID, const std::string& strTenTaiKhoan, const std::string& strLoaiTienTe, long long llSoDu) {
    UserAccount newUser(strID, DEFAULT_PIN, strTenTaiKhoan, llSoDu, strLoaiTienTe, false, true);
    this->_listUsers.insert(strID, newUser);
    
    //cập nhật danh sách
    string strFileIDName = strID + ".txt";
    ofstream fileOutput1(strFileIDName);


    //tạo file id.txt mới
    if (fileOutput1.is_open())
    {
        fileOutput1 << strID << "\n";
        fileOutput1 << strTenTaiKhoan << "\n";
        fileOutput1 << 0 << "\n";
        fileOutput1 << "VND" << "\n";

        fileOutput1.close(); 
        return true;
    }
    return false;

    //tạo file lịch sử .txt mới
    string strFileLSName = "LichSu" + strID + ".txt"; 
    ofstream fileOutput2(strFileLSName);
    if (fileOutput2.is_open())
    {
        fileOutput2.close(); 
        return true;
    }
    return false;

    //cập nhật file thetu.txt
    ofstream fileOutput3("CARD_LIST_FILE_NAME", ios::app);
    if (!fileOutput3.is_open()) return false;
    fileOutput3  << newUser.getID() << " " << DEFAULT_PIN << endl;
    fileOutput3.close();

    return true;
}

bool DataRepository::deleteUser(const std::string& strID) {
    this->_listUsers.erase(strID);

    string filename1 = "LichSu" + strID + ".txt";
    string filename2 = strID + ".txt";

    if (remove(filename1.c_str()) == 0 && remove(filename2.c_str()) == 0) 
    {
    }
    else return false;
    
    ofstream fout(CARD_LIST_FILE_NAME, ios::trunc);
    if (!fout) {
        return false;
    }
    _listUsers.for_each([&](const string& id, const UserAccount& user) {
        fout << id << " " << user.getPin() << '\n';
        });
    fout.close();

    return true;
}

bool DataRepository::updatePin(const std::string& id, const std::string& pinMoi) {
    auto user = _listUsers.find(id);
    user->setPin(pinMoi);

    ofstream fout(CARD_LIST_FILE_NAME, ios::trunc);
    if (!fout) {
        return false;
    }
    _listUsers.for_each([&](const string& id, const UserAccount& user) {
        fout << id << " " << user.getPin() << '\n';
        });
    fout.close();

    return true;
}