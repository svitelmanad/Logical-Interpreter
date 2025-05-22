#pragma once
#include "blackboard.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <queue>

class Evaluator
{
public:
    Evaluator();
    ~Evaluator() {}
    void evaluate(Blackboard& board);

private:
    bool evaluateComparison(std::string& left, std::string& op, std::string& right);
    bool evaluateExpression(const std::string& expr, Blackboard& board, int num);
    std::vector<std::string> tokenize(const std::string& expr);
};