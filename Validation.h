// Validation.h
#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

namespace Validation {
    bool isDigit(char c);
    bool isAlpha(char c);

    bool isAllDigits(const std::string& s);
    bool isValidIDFormat(const std::string& id);
    bool isValidNameFormat(const std::string& id);
    bool withdrawInput(const std::string& input);
    bool isValidPin(const std::string& pin);
}

#endif
