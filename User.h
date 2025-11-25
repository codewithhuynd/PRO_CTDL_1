#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <string>


class UserAccount
{
public:
    UserAccount()
        : _strID(""), _strPin(""), _strAccountName(""),
        _lBalance(0.0f), _strCurrency("VND"),
        _iFailCount(0), 
        _bIsLocked(false), _bIsFirstLogin(true)
    {
    }

    UserAccount(const std::string& strID,
        const std::string& strPin,
        const std::string& strAccountName,
        long long fBalance,
        const std::string& strCurrency,
        bool bIsLocked = false,
        bool bIsFirstLogin = true)
        : _strID(strID), _strPin(strPin), _strAccountName(strAccountName),
        _lBalance(fBalance), _strCurrency(strCurrency),
        _iFailCount(0),
        _bIsLocked(bIsLocked), _bIsFirstLogin(bIsFirstLogin)
    {
    }

    UserAccount(const UserAccount& other)
        : _strID(other._strID), _strPin(other._strPin), _strAccountName(other._strAccountName),
        _lBalance(other._lBalance), _strCurrency(other._strCurrency),
        _iFailCount(other._iFailCount), 
        _bIsLocked(other._bIsLocked), _bIsFirstLogin(other._bIsFirstLogin)
    {
    }

    UserAccount& operator=(const UserAccount& other)
    {
        if (this != &other)
        {
            _strID = other._strID;
            _strPin = other._strPin;
            _strAccountName = other._strAccountName;
            _lBalance = other._lBalance;
            _strCurrency = other._strCurrency;
            _iFailCount = other._iFailCount; 
            _bIsLocked = other._bIsLocked;
            _bIsFirstLogin = other._bIsFirstLogin;
        }
        return *this;
    }

    ~UserAccount() = default;
    std::string getID() const { return _strID; }
    std::string getPin() const { return _strPin; }
    std::string getAccountName() const { return _strAccountName; }
    long long getBalance() const { return _lBalance; }
    std::string getCurrency() const { return _strCurrency; }
    bool isLocked() const { return _bIsLocked; }
    bool isFirstLogin() const { return _bIsFirstLogin; }
    int getFailCount() const { return _iFailCount; }

    void setID(const std::string& id) { _strID = id; }
    void setPin(const std::string& pin) { _strPin = pin; }
    void setAccountName(const std::string& name) { _strAccountName = name; }
    void setBalance(long long balance) { _lBalance = balance; }
    void setCurrency(const std::string& currency) { _strCurrency = currency; }
    void setLocked(bool locked) { _bIsLocked = locked; }
    void setFirstLogin(bool firstLogin) { _bIsFirstLogin = firstLogin; }
    void increaseFailCount() { _iFailCount++; }
    void setFailCount(int fc) { _iFailCount = fc; }

private:
   
    std::string _strID;            
    std::string _strAccountName;   
    long long       _lBalance;        
    std::string _strCurrency;      
    std::string _strPin;
    int _iFailCount;
    bool        _bIsLocked;       
    bool        _bIsFirstLogin;    
};

#endif // USERACCOUNT_H