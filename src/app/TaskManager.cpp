#include <fstream>
#include <algorithm>
#include <iostream>

#include "TaskManager.h"
#include "utils/FileHandler.h"

// Add a new task
void TaskManager::addTask(const Task& task)
{
    tasks.push_back(task);
}

// Remove a task by ID
bool TaskManager::removeTask(int id)
{
    auto it = std::remove_if(tasks.begin(), tasks.end(), 
        [id](const Task& t)
        {
            return t.getId() == id;
        });
    
    if (it != tasks.end()) 
    {
        tasks.erase(it, tasks.end());
        return true;
    }
    return false;
}

// Find a task by ID
Task* TaskManager::findTask(int id)
{
    for (auto& task : tasks)
    {
        if (task.getId() == id)
            return &task;
    }
    return nullptr;
}

// List all tasks
std::vector<Task> TaskManager::listTasks() const
{
    return tasks;
}

// filter tasks by status
std::vector<Task> TaskManager::listTasksByStatus(Status status) const
{
    std::vector<Task> filtered;
    for (const auto& task : tasks)
    {
        if (task.getStatus() == status)
            filtered.push_back(task);
    }
    return filtered;
}

// Sort tasks by priority (High > Medium > Low)
void TaskManager::sortTasksByPriority()
{
    std::sort(tasks.begin(), tasks.end(),
        [](const Task& a, const Task& b)
        {
            return static_cast<int>(a.getPriority()) > static_cast<int>(b.getPriority());
        });
}

// Load from file through FileHandler
bool TaskManager::loadFromFile(const std::string& filepath) 
{
    tasks.clear();
    return FileHandler::loadTasksFromFile(filepath, tasks);
}

// Save to file through FileHandler
bool TaskManager::saveToFile(const std::string& filepath) const 
{
    return FileHandler::saveTasksToFile(filepath, tasks);
}
