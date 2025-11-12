// TheTu.h
#pragma once
#include <string>
#include <sstream>

class TheTu {
private:
    string _strID;
    string _strMaPIN;
    int _iLoginAttempts;
    bool _bIsLocked;

public:
    TheTu() : _strID(""), _strMaPIN(""), _iLoginAttempts(0), _bIsLocked(false) {}

    TheTu(const string& strID, const string& strPIN)
        : _strID(strID), _strMaPIN(strPIN), _iLoginAttempts(0), _bIsLocked(false) {
    }

    string getID() const { return _strID; }
    string getMaPIN() const { return _strMaPIN; }
    int getLoginAttempts() const { return _iLoginAttempts; }
    bool isLocked() const { return _bIsLocked; }

    void setMaPIN(const string& newPIN) { _strMaPIN = newPIN; }
    void incrementLoginAttempts() { ++_iLoginAttempts; }
    void resetLoginAttempts() { _iLoginAttempts = 0; }
    void setIsLocked(bool bLock) { _bIsLocked = bLock; }

    string toString() const {
        ostringstream oss;
        oss << _strID << ' ' << _strMaPIN;
        return oss.str();
    }

    // fromString: ??c dòng có d?ng "ID PIN" (cách nhau b?i whitespace)
    void fromString(const string& lineData) {
        istringstream iss(lineData);
        string id, pin;
        if (!(iss >> id)) {
            // dòng r?ng ho?c không h?p l? -> ??t m?c ??nh
            _strID.clear();
            _strMaPIN.clear();
            _iLoginAttempts = 0;
            _bIsLocked = false;
            return;
        }
        if (!(iss >> pin)) {
            // ch? có ID, không có PIN -> ??t PIN r?ng
            pin.clear();
        }
        _strID = id;
        _strMaPIN = pin;
        // Khi file ch? l?u ID và PIN, ??t các tr??ng tr?ng thái m?c ??nh
        _iLoginAttempts = 0;
        _bIsLocked = false;
    }

    // Optional: operator== if you ever compare TheTu objects
    bool operator==(const TheTu& other) const {
        return _strID == other._strID
            && _strMaPIN == other._strMaPIN
            && _iLoginAttempts == other._iLoginAttempts
            && _bIsLocked == other._bIsLocked;
    }
};
