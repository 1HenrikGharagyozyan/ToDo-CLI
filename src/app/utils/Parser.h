#pragma once

#include <string>
#include <vector>

struct Command
{
    std::string name;
    std::vector<std::string> args;
};

class Parser
{
public:
    static Command parse(int argc, char* argv[]);
};