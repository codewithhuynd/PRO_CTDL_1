// Validation.cpp
#include "Validation.h"

namespace Validation {

    


    bool isAllDigits(const std::string& s) {
        if (s.empty()) return false;
        for (char c : s) if (c > '9' || c < '0') return false;
        return true;
    }

    bool isValidIDFormat(const std::string& id) {
        if (id.size() != 14) return false;
        if (!isAllDigits(id)) return false;
        return true;
    }

    bool isAlpha(char c) {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    bool isValidNameFormat(const std::string& name) {
        if (name.empty()) return false;
        if (name.size() > 50) return false;     

        if (name.front() == ' ' || name.back() == ' ') return false;

        for (char c : name) {
            if (!isAlpha(c) && !isDigit(c) && c != ' ' && c != '_')
                return false; 
        }
        return true; 
    }

    bool withdrawInput(const std::string& input) {

        if (input.empty()) return false;

        if (!isAllDigits(input)) return false;

        long long value = 0;

        try {
            value = stoll(input);
        }
        catch (...) {
            return false; 
        }

        if (value <= 0) return false;

        return true;
    }

}
