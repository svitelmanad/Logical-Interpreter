#pragma once
#include "blackboard.h"
#include <string>
#include <cctype>
#include <iostream>

class Validator
{
public:
    Validator();
    ~Validator() {}
    void validate(Blackboard& board);

private:
    bool checkParentheses(const std::string& expr);
    bool containsOnlyAllowedCharacters(const std::string& expr);
    std::string findInvalidCharacters(const std::string& expr);
    std::string checkInvalidOperatorSequences(const std::string& expr);
    std::string checkInvalidOperators(const std::string& expr);
    bool isContainsCyrillic(const std::string& expr);

};