#include "UserManager.h"
#include <conio.h>
#include <windows.h>
#include<cstdio>
#include <fstream>
#include"User.h"
#include"AdminManager.h"
#include"MyUnorderedMap.h"

UserManager::UserManager(){}

pair<bool,string> UserManager::loginUser(DataRepository& mainData)
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
            else return { false,"" };
        }

        UserAccount& realUser = *userPtr;

        
        if (realUser.isLocked()) { 
            atmview.displayUserLoginForm();
            return { false,"" };
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
                    return { false,"" };
                }
                idFile << realUser.getID() << "\n";
                idFile << realUser.getAccountName() << "\n";
                idFile << realUser.getBalance() << "\n";
                idFile << realUser.getCurrency() << "\n";
                idFile << "BI KHOA" << "\n";
                idFile.close();

                atmview.accountLocked();
                return { false,"" };
            }

            string choice = atmview.loginUserFailFrame(); 
            if (choice == "1") continue; 
            else return { false,"" };
        }

        
        realUser.setFailCount(0);
        mainData.setUserList(listUsers);

        if (realUser.getPin() == DEFAULT_PIN) {
            changePin(mainData, realUser);
        }

        return { true,realUser.getID() };
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

    atmview.changePinSuccessFrame();
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
bool UserManager::transferMoney(DataRepository& mainData, const UserAccount& currentUser) {
    ATMView atmview;
    bool inputCorect = false;
    pair<string, long long> nguoiNhan;
    MyUnorderedMap<string, UserAccount> listUser = mainData.getUserList();
    UserAccount* userReceive = nullptr;
    while (!inputCorect) {
        nguoiNhan = atmview.transferMoneyFrame();
        userReceive = listUser.find(nguoiNhan.first);
        if (userReceive==nullptr
            ||userReceive->getID()==currentUser.getID()
            ||nguoiNhan.second< MIN_WITHDRAWAL_AMOUNT
            ||nguoiNhan.second>currentUser.getBalance()- MIN_REMAINING_BALANCE
            ||nguoiNhan.second%MIN_REMAINING_BALANCE!=0)
        {
            string strChoice = atmview.transferMoneyFailFrame();
            if (strChoice == "1")
                continue;
            else
                return false;
        }
        inputCorect = true;
    }

    auto crUser = listUser.find(currentUser.getID());
    long long newBalance = currentUser.getBalance() - nguoiNhan.second;
    crUser->setBalance(newBalance);

    long long newBalance2 = userReceive->getBalance() + nguoiNhan.second;
    userReceive->setBalance(newBalance2);

    mainData.setUserList(listUser);

    std::ofstream idFile1(crUser->getID() + ".txt");
    if (!idFile1) {
        std::cerr << "Khong the mo file " << crUser->getID() << ".txt\n";
        return false;
    }
    idFile1 << crUser->getID() << "\n";
    idFile1 << crUser->getAccountName() << "\n";
    idFile1 << crUser->getBalance() << "\n";
    idFile1 << crUser->getCurrency() << "\n";
    if (crUser->isLocked()) {
        idFile1 << "BI KHOA" << "\n";
    }else
        idFile1 << "KHONG BI KHOA" << "\n";
    idFile1.close();

    std::ofstream idFile2(userReceive->getID() + ".txt");
    if (!idFile2) {
        std::cerr << "Khong the mo file " << userReceive->getID() << ".txt\n";
        return false;
    }
    idFile2 << userReceive->getID() << "\n";
    idFile2 << userReceive->getAccountName() << "\n";
    idFile2 << userReceive->getBalance() << "\n";
    idFile2 << userReceive->getCurrency() << "\n";
    if (userReceive->isLocked()) {
        idFile2 << "BI KHOA" << "\n";
    }
    else
        idFile2 << "KHONG BI KHOA" << "\n";
    idFile2.close();

    time_t now = time(0);
    std::tm localTime;
    localtime_s(&localTime, &now);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S %d-%m-%Y", &localTime);

    std::string filename1 = "LichSu" + crUser->getID() + ".txt";
    std::ofstream file1(filename1, std::ios::app);
    if (file1.is_open()) {
        file1 << "CHUYEN TIEN " << userReceive->getID() << " " << userReceive->getAccountName() << " " << nguoiNhan.second << " VND, vao luc " << buffer << "\n";
        file1.close();
    }
    else {
        return false;
    }

    std::string filename2 = "LichSu" + userReceive->getID() + ".txt";
    std::ofstream file2(filename2, std::ios::app);
    if (file2.is_open()) {
        file2 <<"NHAN TIEN TU " << crUser->getID() << " " << crUser->getAccountName() << " " << nguoiNhan.second << " VND, vao luc " << buffer << "\n";
        file2.close();
    }
    else {
        return false;
    }

    atmview.transferMoneySuccessFrame();
    return true;
}
void UserManager::runUserMenu(DataRepository& mainData,const string& id)
{
    ATMView atmview;

    while (true)
    {
        int iChoice = atmview.displayUserMenu();
        MyUnorderedMap<string, UserAccount> listUser = mainData.getUserList();
        auto crUser = listUser.find(id);
        switch (iChoice)
        {
        case 1:
            
            atmview.displayUserInfo(*crUser);
            break;

        case 2:
            withdrawMoney(mainData,*crUser);
            break;
        case 3:
            transferMoney(mainData,*crUser);
            break;

        case 4:
            atmview.displayTransactionHistory(id);
            break;

        case 5:
            changePin(mainData, *crUser);
            break;
        case 6:
            return;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai chuc nang (1-6).\n";
            break;
        }
    }
}
