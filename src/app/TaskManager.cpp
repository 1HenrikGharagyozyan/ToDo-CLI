#include <algorithm>

#include "TaskManager.h"
#include "utils/FileHandler.h"

// Add a new task
void TaskManager::addTask(const Task &task)
{
    _tasks.push_back(task);
}

// Remove a task by ID
bool TaskManager::removeTask(const std::string &id)
{
    auto it = std::remove_if(_tasks.begin(), _tasks.end(),
                             [id](const Task &t)
                             {
                                 return t.getId() == id;
                             });

    if (it != _tasks.end())
    {
        _tasks.erase(it, _tasks.end());
        return true;
    }
    return false;
}

// Find a task by ID
Task *TaskManager::findTask(const std::string &id)
{
    for (auto &task : _tasks)
    {
        if (task.getId() == id)
            return &task;
    }
    return nullptr;
}

std::vector<Task> TaskManager::listTasks() const
{
    return _tasks;
}

std::vector<Task> TaskManager::listByStatus(Status status) const
{
    std::vector<Task> result;
    for (const auto &task : _tasks)
    {
        if (task.getStatus() == status)
            result.push_back(task);
    }
    return result;
}

std::vector<Task> TaskManager::listByPriority(Priority priority) const
{
    std::vector<Task> result;
    for (const auto &task : _tasks)
    {
        if (task.getPriority() == priority)
            result.push_back(task);
    }
    return result;
}

void TaskManager::sortByPriority()
{
    std::sort(_tasks.begin(), _tasks.end(),
              [](const Task &a, const Task &b)
              {
                  return static_cast<int>(a.getPriority()) >
                         static_cast<int>(b.getPriority());
              });
}

// Load from file through FileHandler
bool TaskManager::loadFromFile(const std::string &filepath)
{
    _tasks.clear();
    return FileHandler::loadTasksFromFile(filepath, _tasks);
}

// Save to file through FileHandler
bool TaskManager::saveToFile(const std::string &filepath) const
{
    return FileHandler::saveTasksToFile(filepath, _tasks);
}
