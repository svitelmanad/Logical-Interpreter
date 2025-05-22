#include "input.h"

InputHandler::InputHandler()
{

}

//������ ���������, �������� ��� ������� ���������
void InputHandler::readFromArguments(const std::vector<std::string>& args, Blackboard& board)
{
    for (int i = 0; i < args.size(); i++)
    {
        std::string line = args[i];
        processLine(line, board, i);
    }
}

//������ ���������, �������� � ������������� ������
void InputHandler::readInteractive(Blackboard& board, std::string inputText)
{
    std::istringstream iss(inputText);
    std::string line;
    int line_num = 1;
    while (getline(iss, line))
    {
        if (trim(line).empty())
            continue;
        processLine(line, board, line_num++);
    }
}

//������ ���������, �������� � ��������� �����
std::vector<std::string> InputHandler::readFromFile(const std::string& file, Blackboard& board)
{
    std::vector<std::string> lines;
    std::ifstream file_(file);
    if (!file_.is_open())
    {
        board.addError("�� ������� ������� ����: " + file);
        return lines;
    }

    std::string line;
    int line_num = 1;
    while (std::getline(file_, line))
    {
        lines.push_back(line);
        processLine(line, board, line_num++);
    }
    file_.close();

    return lines;
}

//�������� �������� �� ������ ������
std::string InputHandler::trim(const std::string& str)
{
    size_t begin = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    std::string rez = (begin != std::string::npos) ? str.substr(begin, end - begin + 1) : "";
    return rez;
}

//��������� ����� �� ������ ��������
bool InputHandler::isParameterLine(const std::string& line)
{
    return line.find("=") != std::string::npos && line.find_first_of("><!") == std::string::npos && line.find("==") == std::string::npos && line.find("[") == std::string::npos;
}

//��������� ������ � �� ���������� �� ����� (���������� �������� ��������� � ����������)
void InputHandler::processLine(const std::string& line, Blackboard& board, int line_num)
{
    std::string trimmed = trim(line);
    if (trimmed.empty())
        return;

    if (isParameterLine(trimmed))
    {
        size_t equal_pos = trimmed.find("=");
        if (equal_pos != std::string::npos && equal_pos != 0)
        {
            std::string name = trim(trimmed.substr(0, equal_pos));
            std::string value = trim(trimmed.substr(equal_pos + 1));
            if (name.find_first_of("0123456789.-") != std::string::npos)
                board.addError("������ � ������ " + std::to_string(line_num) + ": ��� ��������� ����� ��������� ������ ��������� ����� � '_'");
            if (value.find_first_not_of("0123456789-.") != std::string::npos)
            {
                value = (value[0] != '\"') ? ('\"' + value) : value;
                value += (value[value.length() - 1] != '\"') ? '\"' : ' ';
            }
            board.addParameter(name, value);
        }
        else
            board.addError("������ � ������ " + std::to_string(line_num) + ": ������������ ��������");
    }
    else
        board.addExpression(trimmed);
}
