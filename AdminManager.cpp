#include "AdminManager.h"
#include <conio.h>
#include <windows.h>
#include<cstdio>
#include"UserManager.h"
#include"Constants.h"
#include"Validation.h"





AdminManager::AdminManager()
{
}

bool AdminManager::loginAdmin(const MyUnorderedMap<std::string, Admin>& admins)
{
    ATMView atmview;
    Admin loginAdmin; 
    bool lgAdminSuccess = false;


    while (true) {
        loginAdmin = atmview.displayAdminLoginFrame();

        auto adminCheck = admins.find(loginAdmin.getUser());

        if (adminCheck== nullptr || adminCheck->getPass()!=loginAdmin.getPass()) {

            string strChoice = atmview.loginAdminFailFrame();
            if (strChoice == "1")
                continue;
            else
                return false;
        }
        lgAdminSuccess = true;
        break;
    }

    return lgAdminSuccess;
}

bool AdminManager::addAccountUser(DataRepository& mainData) {
    ATMView atmview;
    bool inputCorect = false;
    UserAccount newUser;
    MyUnorderedMap<string, UserAccount> listUser = mainData.getUserList();
    while (!inputCorect) {
        newUser = atmview.displayAddUserFrame();

        auto userCheck = listUser.find(newUser.getID());
        if (userCheck != nullptr 
            || !Validation::isValidIDFormat(newUser.getID()) 
            || !Validation::isValidNameFormat(newUser.getAccountName()) 
            || newUser.getCurrency()!="VND"
            || newUser.getBalance()<0) 
        {
            string strChoice = atmview.addUserFailFrame();
            if (strChoice == "1")
                continue;
            else
                return false;
        }
        inputCorect = true;
    }
    
    listUser.insert(newUser.getID(), newUser);
    mainData.setUserList(listUser);

    std::ofstream idFile(newUser.getID() + ".txt");
    if (!idFile) {
        std::cerr << "Khong the tao file " << newUser.getID() << ".txt\n";
        return false;
    }
    idFile <<  newUser.getID() << "\n";
    idFile << newUser.getAccountName() << "\n";
    idFile << newUser.getBalance()<< "\n";
    idFile << newUser.getCurrency() << "\n";
    idFile << "KHONG BI KHOA" << "\n";
    idFile.close();

    std::ofstream idFile2("LichSu"+newUser.getID() + ".txt");
    if (!idFile2) {
        std::cerr << "Khong the tao file LichSu" << newUser.getID() << ".txt\n";
        return false;
    }
    idFile
    idFile2.close();

    ofstream fout(CARD_LIST_FILE_NAME, ios::trunc);
    if (!fout) {
        return false;
    }
    listUser.for_each([&](const string& id, const UserAccount& user) {
        fout << id << " " << user.getPin() << '\n';
        });
    fout.close();

    atmview.addUserSuccessFrame();
    return true;
}

bool AdminManager::deleteAccountUser(DataRepository& mainData) {
    ATMView atmview;
    bool inputCorect = false;
    string strID;
    UserAccount* userCheck;
    MyUnorderedMap<string, UserAccount> listUser = mainData.getUserList();
    while (!inputCorect) {
        strID = atmview.deleteAccountUserFrame();

        userCheck = listUser.find(strID);
        if (userCheck == nullptr || !Validation::isValidIDFormat(strID))
        {
            string strChoice = atmview.deleteAccountUserFailFrame();
            if (strChoice == "1")
                continue;
            else
                return false;
        }
        inputCorect = true;
    }

    listUser.erase(strID);
    string file1 = strID+".txt";
    string file2 = "LichSu"+strID+".txt";

    if (remove(file1.c_str()) == 0) {
    }
    else {
        return false;
    }

    if (remove(file2.c_str()) == 0) {
    }
    else {
        return false;
    }

    mainData.setUserList(listUser);
    ofstream fout(CARD_LIST_FILE_NAME, ios::trunc);
        if (!fout) {
            return false;
        }
        listUser.for_each([&](const string& id, const UserAccount& user) {
            fout << id << " " << user.getPin() << '\n';
            });
        fout.close();
        atmview.deleteUserSuccessFrame();
        return true;
}

bool AdminManager::unlockAccountUser(DataRepository& mainData) {
    ATMView atmview;
    std::string strID;
    MyUnorderedMap<std::string, UserAccount> listUserLock = mainData.getUserListLock();
    MyUnorderedMap<std::string, UserAccount> listUser = mainData.getUserList();
    UserAccount* userPtr1 = nullptr;
    UserAccount* userPtr2 = nullptr;
    bool inputCorrect = false;
    while (!inputCorrect) {
        if (listUserLock.empty()) {
            atmview.listUsersLockEmpty();
            return false;
        }
        else {
            atmview.displayListUsersLock(listUserLock);
            strID = atmview.unlockAccountUserFrame();
        }
       
        userPtr1 = listUser.find(strID);
        userPtr2 = listUserLock.find(strID); 
        if (userPtr2 == nullptr) {
            std::string strChoice = atmview.unlockAccountUserFailFrame();
            if (strChoice == "1") {
                continue; 
            }
            else {
                return false; 
            }
        }

       
        inputCorrect = true;
    }
    userPtr1->setLocked(false);
    mainData.setUserList(listUser);

    listUserLock.erase(strID);
    mainData.setUserListLock(listUserLock);
    atmview.unlockAccountUserSuccess();

    std::ofstream idFile(strID + ".txt");
    if (!idFile) {
        std::cerr << "Khong the tao file " << strID << ".txt\n";
        return false;
    }
    idFile << strID << "\n";
    idFile << userPtr1->getAccountName() << "\n";
    idFile << userPtr1->getBalance() << "\n";
    idFile << userPtr1->getCurrency() << "\n";
    idFile << "KHONG BI KHOA" << "\n";
    idFile.close();
    return true;
}

void AdminManager::runAdminMenu(DataRepository& mainData)
{
    ATMView atmview;

    while (true)
    {
        int iChoice = atmview.displayAdminMenu();

        switch (iChoice)
        {
        case 1: 
            atmview.displayCardList(mainData.getUserList());
            break;

        case 2: 
            addAccountUser(mainData);
            break;

        case 3: 
            deleteAccountUser(mainData);
            break;

        case 4: 
            unlockAccountUser(mainData);
            break;

        case 5: 
            return; 
        default:
            cout << "\033[91mLua chon khong hop le. Vui long chon lai chuc nang (1-5).\n";
            break;
        }
    }
}




