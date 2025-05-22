#include "blackboard.h"

Blackboard::Blackboard()
{

}

Blackboard::~Blackboard()
{

}

//Добавление параметра на доску
void Blackboard::addParameter(const std::string& name, const std::string& value)
{
    parameters[name] = value;
}

//Добавление строки на доску (без подстановки параметров)
void Blackboard::addExpression(const std::string& expr)
{
    expressions.push_back(expr);
}

//Добавление ошибки на доску
void Blackboard::addError(const std::string& errorMessage)
{
    errors.push_back(errorMessage);
}

//Добавление логического выражения на доску
void Blackboard::addFinalExpression(const std::string& expr)
{
    final_expressions.push_back(expr);
}

//Добавление результата обработки логического выражения на доску
void Blackboard::addResult(const std::string& result)
{
    results.push_back(result);
}

//Получение значения параметра по его имени
std::string Blackboard::getParameter(const std::string& name) const
{
    auto it = parameters.find(name);
    if (it != parameters.end()) {
        return it->second;
    }
    return "";
}

//Получение строки по индексу
std::string Blackboard::getExpression(size_t index)
{
    return expressions[index];
}

//Получение количества строк (логические выражения без подстановки параметров)
size_t Blackboard::getExpressionsNum()
{
    return expressions.size();
}

//Получение количества логических выражений
size_t Blackboard::getFinalExpressionsNum()
{
    return final_expressions.size();
}

//Получение логического выражения по индексу
std::string Blackboard::getFinalExpression(size_t index)
{
    return final_expressions[index];
}

//Получение списка ошибок
const std::vector<std::string>& Blackboard::getErrors() const
{
    return errors;
}

//Формирование вывода (результаты или список ошибок)
std::string Blackboard::printResult()
{
    std::string result;
    if (!errors.empty())
    {
        result += "Ошибки:\n";
        for (size_t i = 0; i < errors.size(); i++)
            result += std::to_string(i + 1) + ". " + errors[i] + "\n";
    }
    else if (final_expressions.empty())
        result = "Выражения не были заданы";
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

//Очистка атрибутов доски
void Blackboard::clear()
{
    parameters.clear();
    expressions.clear();
    final_expressions.clear();
    errors.clear();
    results.clear();
}
