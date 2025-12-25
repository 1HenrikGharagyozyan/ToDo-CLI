#include "FileHandler.h"

#include <fstream>
#include <iostream>

bool FileHandler::saveTasksToFile(const std::string& filepath, const std::vector<Task>& tasks)
{
    std::ofstream ofs(filepath);
    if (!ofs.is_open())
        return false;

    for (const auto &task : tasks)
        ofs << task.serialize() << "\n";
    ofs.close();
    return true;
}

bool FileHandler::loadTasksFromFile(const std::string& filepath, std::vector<Task>& tasks)
{
    std::ifstream ifs(filepath);
    if (!ifs.is_open())
        return false;       
    std::string line;
    while (std::getline(ifs, line))
    {
        try
        {               
            Task task = Task::deserialize(line);
            tasks.push_back(task);
        }
        catch (const std::exception &e)
        {
            // Handle malformed line (skip or log)
            continue;
        }
    }
    ifs.close();
    return true;
}