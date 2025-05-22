#include "validator.h"

Validator::Validator()
{

}

//�������� ��������� �� ������� ������������ ���������
void Validator::validate(Blackboard& board)
{
    int line_num = 0;

    for (size_t i = 0, j = board.getFinalExpressionsNum(); i < j; i++)
    {
        std::string expr = board.getFinalExpression(i);
        std::string ops;
        line_num++;

        if (!checkParentheses(expr))
            board.addError("������ � ��������� " + std::to_string(line_num) + ": ������������������ ������ " + expr);

        if (isContainsCyrillic(expr))
            board.addError("������ � ��������� " + std::to_string(line_num) + ": ��������� ������ ��������� ������ ��������� �������");

        else if (!containsOnlyAllowedCharacters(expr))
            board.addError("������ � ��������� " + std::to_string(line_num) + "(" + expr + "): ������������ ������������ ������� " + findInvalidCharacters(expr));

        ops = checkInvalidOperatorSequences(expr);
        if (!ops.empty())
            board.addError("������ � ��������� " + std::to_string(line_num) + ": ������ ��������� (" + ops + ")");

        ops = checkInvalidOperators(expr);
        if (!ops.empty())
            board.addError("������ � ��������� " + std::to_string(line_num) + ": ������������ �������� (" + ops + ")");
    }
}

//�������� ������������������ ������ � ���������
bool Validator::checkParentheses(const std::string& expr)
{
    int count = 0;
    for (char el : expr)
    {
        if (el == '(')
            count++;
        else if (el == ')')
            count--;
    }

    return count == 0;
}

//�������� �� ������� ������������ ��������
bool Validator::containsOnlyAllowedCharacters(const std::string& expr)
{
    for (size_t i = 0; i < expr.length(); i++)
    {
        char el = expr[i];
        if (!std::isalnum(el) && el != ' ' && el != '>' && el != '<' && el != '=' && el != '!' && el != '(' && el != ')' && el != '[' && el != ']' && el != '_' && el != '\"' && el != '-' && el != '.')
            return false;
    }

    return true;
}

//���������� ������������ �������� � ���������
std::string Validator::findInvalidCharacters(const std::string& expr)
{
    std::string characters;
    for (char el : expr)
    {
        if (!std::isalnum(el) && el != ' ' && el != '>' && el != '<' && el != '=' && el != '!' && el != '(' && el != ')' && el != '[' && el != ']' && el != '_' && el != '\"' && el != '-' && el != '.')
        {
            characters += el;
            characters += " ";
        }
    }

    return characters;
}

//�������� �� ������� ������ ������ ����������
std::string Validator::checkInvalidOperatorSequences(const std::string& expr)
{
    std::vector<std::string> operators{ "==", ">=", "<=", "!=", ">", "<", "OR", "AND" };
    std::string ops;
    size_t pos = 0;

    while (pos < expr.length())
    {
        size_t op_len = 0;
        std::string op;
        pos = expr.find_first_of("><=!OA", pos);
        if (pos >= expr.length())
            break;
        for (int i = 0; i < operators.size(); i++)
        {
            op = operators[i];
            if (expr.compare(pos, op.size(), op) == 0)
            {
                ops += op;
                op_len = op.size();
                break;
            }
        }

        if (!ops.empty())
        {
            pos += op_len;
            while (pos < expr.size() && isspace(expr[pos]))
                pos++;

            for (int i = 0; i < operators.size(); i++)
            {
                op = operators[i];
                if (expr.compare(pos, op.size(), op) == 0)
                {
                    ops += op;
                    return ops;
                }
            }
            pos++;
            ops.clear();
        }
        else
            pos++;
    }

    return "";
}

//�������� �� ������� ������������ ���������� (= ��� !) � ���������
std::string Validator::checkInvalidOperators(const std::string& expr)
{
    size_t eq_pos = expr.find("=");
    size_t pos = expr.find("!");
    if (eq_pos != std::string::npos && expr.find_first_of("><!", eq_pos - 1) != eq_pos - 1 && expr.find("=", eq_pos + 1) != eq_pos + 1)
        return "=";
    else if (pos != std::string::npos && pos + 1 < expr.size() && expr[pos + 1] != '=')
        return "!";
    return "";
}

//�������� �� ������� �������� ��������� � ���������
bool Validator::isContainsCyrillic(const std::string& expr)
{
    System::String^ str = gcnew System::String(expr.c_str());
    for each (wchar_t ch in str)
    {
        if ((ch >= L'�' && ch <= L'�') || ch == L'�' || ch == L'�')
            return true;
    }
    return false;
}