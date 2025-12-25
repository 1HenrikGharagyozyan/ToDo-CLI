#pragma once

#include <string>
#include <vector>
#include "../Task.h"

class FileHandler
{
public:
    static bool saveTasksToFile(const std::string &filepath, const std::vector<Task> &tasks);
    static bool loadTasksFromFile(const std::string &filepath, std::vector<Task> &tasks);
};