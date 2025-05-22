#pragma once
#include "blackboard.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class InputHandler
{
public:
    InputHandler();
    ~InputHandler() {}

    void readFromArguments(const std::vector<std::string>& args, Blackboard& board);
    void readInteractive(Blackboard& board, std::string inputText);
    std::vector<std::string> readFromFile(const std::string& file, Blackboard& board);

private:
    std::string trim(const std::string& str);
    bool isParameterLine(const std::string& line);
    void processLine(const std::string& line, Blackboard& board, int line_num);
};