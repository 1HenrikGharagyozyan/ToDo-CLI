#include "Task.h"
#include <stdexcept>
#include <vector>
#include <sstream>

// Конструктор
Task::Task(int id, const std::string& desc, Priority prio, const std::string& dl, Status st)
    : id(id)
    , description(desc)
    , priority(prio)
    , deadline(dl)
    , status(st) 
{
    
}

// Геттеры
int Task::getId() const { return id; }
std::string Task::getDescription() const { return description; }
Priority Task::getPriority() const { return priority; }
std::string Task::getDeadline() const { return deadline; }
Status Task::getStatus() const { return status; }

// Сеттеры
void Task::setDescription(const std::string& desc) { description = desc; }
void Task::setPriority(Priority prio) { priority = prio; }
void Task::setDeadline(const std::string& dl) { deadline = dl; }
void Task::setStatus(Status st) { status = st; }

// Конвертация enum <-> string
std::string Task::priorityToString(Priority p) 
{
    switch(p) 
    {
        case Priority::LOW: 
            return "low";
        case Priority::MEDIUM: 
            return "medium";
        case Priority::HIGH: 
            return "high";
    }
    return "unknown";
}

Priority Task::stringToPriority(const std::string& str) 
{
    if(str == "low") 
        return Priority::LOW;
    if(str == "medium") 
        return Priority::MEDIUM;
    if(str == "high") 
        return Priority::HIGH;
    throw std::invalid_argument("Invalid priority string");
}

std::string Task::statusToString(Status s) 
{
    return s == Status::DONE ? "done" : "pending";
}

Status Task::stringToStatus(const std::string& str) 
{
    if(str == "done") 
        return Status::DONE;
    if(str == "pending") 
        return Status::PENDING;
    throw std::invalid_argument("Invalid status string");
}

// Цветной вывод
std::string Task::toString() const 
{
    std::string color;
    switch(priority) 
    {
    case Priority::LOW: 
        color = TerminalColors::GREEN; 
        break;
    case Priority::MEDIUM: 
        color = TerminalColors::YELLOW; 
        break;
    case Priority::HIGH: 
        color = TerminalColors::RED; 
        break;
    }
    std::ostringstream oss;
    oss << color << "[" << id << "] "
        << description << " | "
        << priorityToString(priority) << " | "
        << deadline << " | "
        << statusToString(status)
        << TerminalColors::RESET;
    return oss.str();
}

// Сериализация в строку для файла
std::string Task::serialize() const 
{
    std::ostringstream oss;
    oss << id << "|" << description << "|" 
        << priorityToString(priority) << "|" 
        << deadline << "|" 
        << statusToString(status);
    return oss.str();
}

// Десериализация из строки
Task Task::deserialize(const std::string& line) 
{
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> parts;

    while(std::getline(iss, token, '|')) 
        parts.push_back(token);
    if(parts.size() != 5)
        throw std::runtime_error("Invalid task format");

    return Task(
        std::stoi(parts[0]),
        parts[1],
        stringToPriority(parts[2]),
        parts[3],
        stringToStatus(parts[4])
    );
}
