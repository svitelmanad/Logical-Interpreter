#include "input.h"

InputHandler::InputHandler()
{

}

//Чтение выражений, заданных как входные аргументы
void InputHandler::readFromArguments(const std::vector<std::string>& args, Blackboard& board)
{
    for (int i = 0; i < args.size(); i++)
    {
        std::string line = args[i];
        processLine(line, board, i);
    }
}

//Чтение выражений, заданных в интерактивном режиме
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

//Чтение выражений, заданных с указанием файла
std::vector<std::string> InputHandler::readFromFile(const std::string& file, Blackboard& board)
{
    std::vector<std::string> lines;
    std::ifstream file_(file);
    if (!file_.is_open())
    {
        board.addError("Не удалось открыть файл: " + file);
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

//Удаление пробелов по концам строки
std::string InputHandler::trim(const std::string& str)
{
    size_t begin = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    std::string rez = (begin != std::string::npos) ? str.substr(begin, end - begin + 1) : "";
    return rez;
}

//Проверяем задаёт ли строка параметр
bool InputHandler::isParameterLine(const std::string& line)
{
    return line.find("=") != std::string::npos && line.find_first_of("><!") == std::string::npos && line.find("==") == std::string::npos && line.find("[") == std::string::npos;
}

//Обработка строки и ее добавление на доску (заполнение массивов выражений и параметров)
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
                board.addError("Ошибка в строке " + std::to_string(line_num) + ": имя параметра может содержать только латинские буквы и '_'");
            if (value.find_first_not_of("0123456789-.") != std::string::npos)
            {
                value = (value[0] != '\"') ? ('\"' + value) : value;
                value += (value[value.length() - 1] != '\"') ? '\"' : ' ';
            }
            board.addParameter(name, value);
        }
        else
            board.addError("Ошибка в строке " + std::to_string(line_num) + ": некорректный параметр");
    }
    else
        board.addExpression(trimmed);
}
