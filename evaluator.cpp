#include "evaluator.h"

Evaluator::Evaluator()
{

}

//���������� ����������� ���������
void Evaluator::evaluate(Blackboard& board)
{
    std::vector<std::string> errors = board.getErrors();
    int line_num = 0;

    for (size_t i = 0, j = board.getFinalExpressionsNum(); i < j; i++)
    {
        std::string expr = board.getFinalExpression(i);
        line_num++;
        if (!expr.empty() && errors.empty())
        {
            bool result = evaluateExpression(expr, board, line_num);
            board.addResult(result ? "true" : "false");
        }
    }
}

//���������� ���������� ��������� (�������� ���������)
bool Evaluator::evaluateComparison(std::string& left, std::string& op, std::string& right)
{
    if (left[0] != '\"' && right[0] != '\"')
    {
        double l = std::stod(left);
        double r = std::stod(right);
        if (op == "==") return l == r;
        if (op == "!=") return l != r;
        if (op == "<")  return l < r;
        if (op == ">")  return l > r;
        if (op == "<=") return l <= r;
        if (op == ">=") return l >= r;
    }
    else
    {
        if (op == "==") return left == right;
        if (op == "!=") return left != right;
    }
    return false;
}

//���������� ���������� ����������� ��������� � ��� �������� �� ������������
bool Evaluator::evaluateExpression(const std::string& expr, Blackboard& board, int num)
{
    std::vector<std::string> tokens = tokenize(expr);
    std::stack<bool> values;
    std::stack<std::string> ops;

    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::string token = tokens[i];
        if (token != "(" && token != ")" && token != "OR" && token != "AND")
        {
            if (token.find_first_not_of(" 0123456789><!=.-") != std::string::npos && token[0] != '\"' && token[token.size() - 1] != '\"')
                board.addError("������ � ��������� " + std::to_string(num) + " : ������������ ������� " + token + " (������ ������ ���� ���������� ���������)");
            if (token.find_first_not_of(" 0123456789-.") == std::string::npos && (token.substr(1).find("-") != std::string::npos || token[token.size() - 1] == '.' || token[0] == '.'))
                board.addError("������ � ��������� " + std::to_string(num) + " : ������������ ����� " + token);
            if (token.find_first_not_of(" 0123456789><!=.-") != std::string::npos && token.find_first_of(".-") != std::string::npos)
                board.addError("������ � ��������� " + std::to_string(num) + " : ������������ ������� " + token + " (������ ����� ��������� ������ ����� � '_')");
        }
    }

    for (size_t i = 0; i < tokens.size();)
    {
        std::string left, right, op;
        std::string token = tokens[i];

        if (token == "(")
        {
            ops.push(token);
            i++;
        }

        else if (token == ")")
        {
            while (!ops.empty() && ops.top() != "(") {
                bool b = values.top();
                values.pop();
                bool a = values.top();
                values.pop();
                std::string op = ops.top();
                ops.pop();
                (op == "AND") ? values.push(a && b) : values.push(a || b);
            }
            if (!ops.empty())
                ops.pop();
            ++i;
        }

        else if (token == "OR" || token == "AND")
        {
            while (!ops.empty() && ops.top() != "(" && (ops.top() == "AND" && token == "AND" || token == "OR"))
            {
                bool b = values.top();
                values.pop();
                bool a = values.top();
                values.pop();
                std::string op = ops.top();
                ops.pop();
                (op == "AND") ? values.push(a && b) : values.push(a || b);
            }

            ops.push(token);
            i++;
        }

        else
        {
            if (i + 2 >= tokens.size())
            {
                token += (i + 1 >= tokens.size()) ? "" : (" " + tokens[i + 1]);
                board.addError("������ � ��������� " + std::to_string(num) + " : �������� ��������� (" + token + ")");
                i += 2;
            }
            else
            {
                left = token;
                op = tokens[i + 1];
                right = tokens[i + 2];

                if (!isalnum(left[0]) && left[0] != '\"' && left[0] != '-')
                    board.addError("������ � ��������� " + std::to_string(num) + " : �������� ����� ������� (" + left + op + ")");
                else if (isalnum(op[0]) || op[0] == '\"' || op[0] == '-')
                    board.addError("������ � ��������� " + std::to_string(num) + " : �������� �������� ���������");
                else if (!isalnum(right[0]) && right[0] != '\"' && right[0] != '-')
                    board.addError("������ � ��������� " + std::to_string(num) + " : �������� ������ �������");
                else if ((left[0] == '\"' && (isdigit(right[0]) || right[0] == '-')) || ((isdigit(left[0]) || left[0] == '-') && right[0] == '\"'))
                    board.addError("������ � ��������� " + std::to_string(num) + " : �������������� ����� (" + left + " � " + right + ")");
                else if (left[0] == '\"' && right[0] == '\"' && op.find_first_of("><") != std::string::npos)
                    board.addError("������ � ��������� " + std::to_string(num) + " : �������� " + op + " �� �������� � �������");
                else if (board.getErrors().empty())
                {
                    bool result = evaluateComparison(left, op, right);
                    values.push(result);
                }
                i += 3;
            }

        }
    }

    if ((values.size() - ops.size()) > 1)
        board.addError("������ � ��������� " + std::to_string(num) + " : �������� ���������� �������� (OR ��� AND)");

    while (!ops.empty() && board.getErrors().empty())
    {
        bool b = values.top();
        values.pop();
        bool a = values.top();
        values.pop();
        std::string op = ops.top();
        ops.pop();
        (op == "AND") ? values.push(a && b) : values.push(a || b);
    }

    return (!values.empty()) ? values.top() : false;
}

//��������� ��������� �� ������
std::vector<std::string> Evaluator::tokenize(const std::string& expr)
{
    std::vector<std::string> tokens;
    std::string token;
    size_t i = 0;

    while (i < expr.length())
    {
        char ch = expr[i];

        if (ch == ' ')
            i++;

        else if (ch == '\"')
        {
            token += ch;
            i++;
            while (i < expr.length())
            {
                token += expr[i];
                if (expr[i] == '\"')
                {
                    i++;
                    break;
                }
                i++;
            }
            tokens.push_back(token);
            token.clear();
        }

        else if (i + 1 < expr.length() && expr[i + 1] == '=' && (ch == '>' || ch == '<' || ch == '=' || ch == '!'))
        {
            token += ch;
            token += '=';
            tokens.push_back(token);
            token.clear();
            i += 2;
        }

        else if (ch == '>' || ch == '<' || ch == '(' || ch == ')')
        {
            token += ch;
            tokens.push_back(token);
            token.clear();
            i++;
        }

        else if (isalnum(ch) || ch == '_' || ch == '.' || ch == '-')
        {
            while (i < expr.length() && (expr[i] == '_' || isalnum(expr[i]) || expr[i] == '-' || expr[i] == '.'))
            {
                if (ch == 'A' && i + 3 < expr.length() && expr.substr(i, 3) == "AND")
                {
                    if (!token.empty())
                    {
                        tokens.push_back(token);
                        token.clear();
                    }
                    tokens.push_back("AND");
                    i += 3;
                }
                else if (ch == 'O' && i + 2 < expr.length() && expr.substr(i, 2) == "OR")
                {
                    if (!token.empty())
                    {
                        tokens.push_back(token);
                        token.clear();
                    }
                    tokens.push_back("OR");
                    i += 2;
                }
                else
                {
                    token += expr[i];
                    i++;
                }
            }

            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
    }

    return tokens;
}
