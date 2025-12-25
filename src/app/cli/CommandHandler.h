#pragma once

#include <string>
#include "../TaskManager.h"
#include "../utils/Parser.h"

class CommandHandler
{
public:
    explicit CommandHandler(TaskManager& manager);

    int handle(const Command& cmd);

private:
    int handleAdd(const Command& cmd);
    int handleList();
    int handleDone(const Command& cmd);
    int handleRemove(const Command& cmd);
    int handleHelp();

private:
    TaskManager& _manager;
};