#include "FileHandler.h"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool FileHandler::loadTasksFromFile(const std::string& filepath, std::vector<Task>& tasks)
{
    std::ifstream in(filepath);
    if (!in.is_open())
        return false;

    json data;
    in >> data;

    if (!data.is_array())
        return false;

    tasks.clear();
    for (const auto& item : data)
        tasks.push_back(Task::fromJson(item));
    return true;
}

bool FileHandler::saveTasksToFile(const std::string& filepath, const std::vector<Task>& tasks)
{
    std::ofstream out(filepath);
    if (!out.is_open())
        return false;

    json data = json::array();
    for (const auto& task : tasks)
        data.push_back(task.toJson());
        
    out << data.dump(4);
    return true;
}
