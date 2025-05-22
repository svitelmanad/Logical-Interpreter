#pragma once
#include "blackboard.h"
#include <string>
#include <vector>

class Parser
{
public:
    Parser();
    ~Parser() {}
    void process(Blackboard& board);

private:
    std::string substituteParams(const std::string& expr, Blackboard& board);
    bool startsWithOperator(const std::string& line);
    bool endsWithOperator(const std::string& line);
    std::string trim(const std::string& str);
};