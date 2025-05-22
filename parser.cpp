#include "parser.h"

Parser::Parser()
{

}

//Обработка выражений и их добавление на доску
void Parser::process(Blackboard& board)
{
    std::vector<std::string> final_expr;
    std::string curr_expr;
    size_t line_num = board.getExpressionsNum();
    bool end_op = 0;

    for (size_t i = 0; i < line_num; i++)
    {
        std::string trimmed = trim(board.getExpression(i));

        if (trimmed.empty())
            continue;

        if (startsWithOperator(trimmed))
        {
            if (curr_expr.empty())
                board.addError("Ошибка в строке " + std::to_string(i + 1) + ": выражение начинается с логического оператора, но предыдущая строка отсутствует");
            else if (!curr_expr.empty() && end_op)
                board.addError("Ошибка в строке " + std::to_string(i + 1) + ": выражение начинается с логического оператора, предыдущая строка им заканчивается");
            else
            {
                curr_expr += " " + trimmed;
            }
            end_op = endsWithOperator(trimmed) ? 1 : 0;
        }
        else if (endsWithOperator(trimmed))
        {
            if (!curr_expr.empty() && !end_op)
            {
                final_expr.push_back(curr_expr);
                curr_expr.clear();
                curr_expr += trimmed;
            }
            else
                curr_expr += (curr_expr.empty() ? "" : " ") + trimmed;
            end_op = 1;
        }
        else
        {
            if (!curr_expr.empty() && !end_op)
            {
                final_expr.push_back(curr_expr);
                curr_expr.clear();
                curr_expr += trimmed;
            }
            else
                curr_expr += (curr_expr.empty() ? "" : " ") + trimmed;
            end_op = 0;
        }
    }

    if (!curr_expr.empty() && end_op)
        board.addError("Ошибка (выражение не завершено): строка " + std::to_string(line_num) + " заканчивается на логический оператор");
    else if (!curr_expr.empty())
        final_expr.push_back(curr_expr);

    for (size_t i = 0; i < final_expr.size(); i++)
    {
        std::string substituted = substituteParams(final_expr[i], board);
        board.addFinalExpression(substituted);
    }
}

//Подстановка параметров в выражения (замена [])
std::string Parser::substituteParams(const std::string& expr, Blackboard& board)
{
    std::string result;
    size_t pos = 0;

    while (pos < expr.length())
    {
        if (expr[pos] == '[')
        {
            size_t end = expr.find("]", pos);
            if (end != std::string::npos && expr.substr(pos + 1, end - pos - 1).find_first_of("=><!-.[") == std::string::npos)
            {
                std::string name = expr.substr(pos + 1, end - pos - 1);
                std::string value = board.getParameter(name);
                if (!value.empty())
                    result += value;
                else
                {
                    board.addError("Ошибка: параметр " + name + " не был задан");
                    result += "[" + name + "]";
                }
                pos = end + 1;
            }
            else
            {
                board.addError("Ошибка: некорректное применение параметра (нет ']')");
                result += expr[pos++];
            }
        }
        else
            result += expr[pos++];
    }

    return result;
}

//Проверка на наличие OR и AND в начале строки
bool Parser::startsWithOperator(const std::string& trimmed)
{
    return (trimmed.substr(0, 3) == "AND" || trimmed.substr(0, 2) == "OR");
}

//Проверка на наличие OR и AND в конце строки
bool Parser::endsWithOperator(const std::string& trimmed)
{
    size_t size = trimmed.length();
    if ((size >= 3 && trimmed.substr(size - 3) == "AND") || (size >= 2 && trimmed.substr(size - 2) == "OR"))
        return true;
    else
        return false;
}

//Удаление пробелов по концам строки
std::string Parser::trim(const std::string& str)
{
    size_t begin = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    std::string rez = (begin != std::string::npos) ? str.substr(begin, end - begin + 1) : "";
    return rez;
}
