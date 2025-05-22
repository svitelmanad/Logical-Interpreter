#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

class Blackboard
{
    std::unordered_map<std::string, std::string> parameters;
    std::vector<std::string> expressions;
    std::vector<std::string> errors;
    std::vector<std::string> final_expressions;
    std::vector<std::string> results;

public:
    Blackboard();
    ~Blackboard();

    void addParameter(const std::string& name, const std::string& value);
    void addExpression(const std::string& expr);
    void addError(const std::string& errorMessage);
    void addFinalExpression(const std::string& expr);
    void addResult(const std::string& result);

    // bool hasParameter(const std::string& name) const;

    std::string getParameter(const std::string& name) const;
    std::string getExpression(size_t index);
    size_t getExpressionsNum();
    size_t getFinalExpressionsNum();
    std::string getFinalExpression(size_t index);
    const std::vector<std::string>& getErrors() const;

    std::string printResult();
    void clear();
};
