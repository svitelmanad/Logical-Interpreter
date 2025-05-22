#include "blackboard.h"

Blackboard::Blackboard()
{

}

Blackboard::~Blackboard()
{

}

//���������� ��������� �� �����
void Blackboard::addParameter(const std::string& name, const std::string& value)
{
    parameters[name] = value;
}

//���������� ������ �� ����� (��� ����������� ����������)
void Blackboard::addExpression(const std::string& expr)
{
    expressions.push_back(expr);
}

//���������� ������ �� �����
void Blackboard::addError(const std::string& errorMessage)
{
    errors.push_back(errorMessage);
}

//���������� ����������� ��������� �� �����
void Blackboard::addFinalExpression(const std::string& expr)
{
    final_expressions.push_back(expr);
}

//���������� ���������� ��������� ����������� ��������� �� �����
void Blackboard::addResult(const std::string& result)
{
    results.push_back(result);
}

//��������� �������� ��������� �� ��� �����
std::string Blackboard::getParameter(const std::string& name) const
{
    auto it = parameters.find(name);
    if (it != parameters.end()) {
        return it->second;
    }
    return "";
}

//��������� ������ �� �������
std::string Blackboard::getExpression(size_t index)
{
    return expressions[index];
}

//��������� ���������� ����� (���������� ��������� ��� ����������� ����������)
size_t Blackboard::getExpressionsNum()
{
    return expressions.size();
}

//��������� ���������� ���������� ���������
size_t Blackboard::getFinalExpressionsNum()
{
    return final_expressions.size();
}

//��������� ����������� ��������� �� �������
std::string Blackboard::getFinalExpression(size_t index)
{
    return final_expressions[index];
}

//��������� ������ ������
const std::vector<std::string>& Blackboard::getErrors() const
{
    return errors;
}

//������������ ������ (���������� ��� ������ ������)
std::string Blackboard::printResult()
{
    std::string result;
    if (!errors.empty())
    {
        result += "������:\n";
        for (size_t i = 0; i < errors.size(); i++)
            result += std::to_string(i + 1) + ". " + errors[i] + "\n";
    }
    else if (final_expressions.empty())
        result = "��������� �� ���� ������";
    else
    {
        for (size_t i = 0, j = 0; i < final_expressions.size(); i++)
            if (!final_expressions[i].empty())
            {
                result += final_expressions[i] + " => " + results[j] + "\n";
                j++;
            }
    }

    return result;
}

//������� ��������� �����
void Blackboard::clear()
{
    parameters.clear();
    expressions.clear();
    final_expressions.clear();
    errors.clear();
    results.clear();
}
