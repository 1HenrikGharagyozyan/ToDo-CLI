#pragma once

#include "Task.h"
#include <vector>
#include <string>

class TaskManager
{
public:
    TaskManager() = default;

    // Work with tasks
    void addTask(const Task& task);
    bool removeTask(const std::string& id);
    Task* findTask(const std::string& id); // Returns pointer to task or nullptr if not found

    const std::vector<Task>& listTasks() const;
    std::vector<Task> listTasksByStatus(Status status) const;
    void sortTasksByPriority();

    // File operations
    bool loadFromFile(const std::string& filepath);
    bool saveToFile(const std::string& filepath) const;

private:
    std::vector<Task> tasks;
};