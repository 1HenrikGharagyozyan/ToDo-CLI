#include "CommandHandler.h"
#include <iostream>

static const std::string DATA_FILE = "tasks.txt";

static Priority parsePriority(const std::string& str)
{
    if (str == "low")
        return Priority::LOW;
    if (str == "medium")
        return Priority::MEDIUM;
    if (str == "high")
        return Priority::HIGH;
    throw std::invalid_argument("Invalid priority: " + str);
}

CommandHandler::CommandHandler(TaskManager& manager)
    : _manager(manager)
{
    // Load tasks from file on initialization
    _manager.loadFromFile(DATA_FILE);
}

int CommandHandler::handle(const Command& cmd)
{
    if (cmd.name == "add")
        return handleAdd(cmd);
    else if (cmd.name == "list")
        return handleList();
    else if (cmd.name == "done")
        return handleDone(cmd);
    else if (cmd.name == "remove")
        return handleRemove(cmd);

    return handleHelp();
}

int CommandHandler::handleAdd(const Command& cmd)
{
    if (cmd.args.size() < 3)
    {
        std::cerr << "Usage: add <description> <priority> <deadline>\n";
        return -1;
    }

    int id = _manager.listTasks().size() + 1;

    Task task(
        id, 
        cmd.args[0],
        parsePriority(cmd.args[1]),
        cmd.args[2],
        Status::PENDING
    );

    _manager.addTask(task);
    _manager.saveToFile(DATA_FILE);
    std::cout << "Task added with ID " << id << "\n";
    return 0;
}

int CommandHandler::handleList()
{
    for (const auto& task : _manager.listTasks())
        std::cout << task.toString() << "\n";
    return 0;
}

int CommandHandler::handleDone(const Command& cmd)
{
    if (cmd.args.size() < 1)
    {
        std::cerr << "Usage: done <task_id>\n";
        return 1;
    }

    int taskId = std::stoi(cmd.args[0]);
    Task* task = _manager.findTask(taskId);
    if (!task)
    {
        std::cerr << "Task not found: " << taskId << "\n";
        return 1;
    }

    task->setStatus(Status::DONE);
    _manager.saveToFile(DATA_FILE);
    std::cout << "Task " << taskId << " marked as done." << "\n";
    return 0;
}

int CommandHandler::handleRemove(const Command& cmd)
{
    if (cmd.args.size() != 1)
    {
        std::cerr << "Usage: remove <task_id>\n";
        return 1;
    }

    int taskId = std::stoi(cmd.args[0]);
    if (!_manager.removeTask(taskId))
    {
        std::cerr << "Task not found: " << taskId << "\n";
        return 1;
    }

    _manager.saveToFile(DATA_FILE);
    std::cout << "Task " << taskId << " removed." << "\n";
    return 0;
}

int CommandHandler::handleHelp()
{
    std::cout <<
        "ToDo CLI\n"
        "Commands:\n"
        "  add <desc> <priority> <deadline>\n"
        "  list\n"
        "  done <id>\n"
        "  remove <id>\n";
    return 0;
}