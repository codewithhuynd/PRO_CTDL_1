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

            if (std::getline(infoFile, line))
            {
                if (line == "BI KHOA") {
                    bIsLocked = true;
                }
                    
                else
                    bIsLocked = false; 
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
        if (newUser.isLocked()) {
            this->_listUsersLock.insert(strID, newUser);
        }
    }

    ifFile.close();
    return true;
}



