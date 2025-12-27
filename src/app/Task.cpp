#include "Task.h"
#include <stdexcept>
#include <vector>
#include <sstream>

#include "utils/TerminalColors.h"

using json = nlohmann::json;

// Конструктор
Task::Task(const std::string& id, const std::string& desc, Priority prio, const std::string& dl, Status st)
    : _id(id)
    , _description(desc)
    , _priority(prio)
    , _deadline(dl)
    , _status(st)
{
}

// Геттеры
std::string Task::getId() const { return _id; }
std::string Task::getDescription() const { return _description; }
Priority Task::getPriority() const { return _priority; }
std::string Task::getDeadline() const { return _deadline; }
Status Task::getStatus() const { return _status; }

// Сеттеры
void Task::setDescription(const std::string &desc) { _description = desc; }
void Task::setPriority(Priority prio) { _priority = prio; }
void Task::setDeadline(const std::string &dl) { _deadline = dl; }
void Task::setStatus(Status st) { _status = st; }

// Конвертация enum <-> string
std::string Task::priorityToString(Priority p)
{
    switch (p)
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

Priority Task::stringToPriority(const std::string &str)
{
    if (str == "low")
        return Priority::LOW;
    if (str == "medium")
        return Priority::MEDIUM;
    if (str == "high")
        return Priority::HIGH;
    throw std::invalid_argument("Invalid priority string");
}

std::string Task::statusToString(Status s)
{
    return s == Status::DONE ? "done" : "pending";
}

Status Task::stringToStatus(const std::string &str)
{
    if (str == "done")
        return Status::DONE;
    if (str == "pending")
        return Status::PENDING;
    throw std::invalid_argument("Invalid status string");
}

// Цветной вывод
std::string Task::toString() const
{
    std::string color;
    switch (_priority)
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
    oss << color << "[" << _id << "] "
        << _description << " | "
        << priorityToString(_priority) << " | "
        << _deadline << " | "
        << statusToString(_status)
        << TerminalColors::RESET;
    return oss.str();
}

// Сериализация в строку для файла
std::string Task::serialize() const
{
    std::ostringstream oss;
    oss << _id << "|" << _description << "|"
        << priorityToString(_priority) << "|"
        << _deadline << "|"
        << statusToString(_status);
    return oss.str();
}

// Десериализация из строки
Task Task::deserialize(const std::string &line)
{
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> parts;

    while (std::getline(iss, token, '|'))
        parts.push_back(token);
    if (parts.size() != 5)
        throw std::runtime_error("Invalid task format");

    return Task{
        parts[0],
        parts[1],
        stringToPriority(parts[2]),
        parts[3],
        stringToStatus(parts[4])
    };
}

json Task::toJson() const
{
    return json{
        {"id", _id},
        {"description", _description},
        {"priority", priorityToString(_priority)},
        {"deadline", _deadline},
        {"status", statusToString(_status)}};
}

Task Task::fromJson(const json& j) 
{
    return Task{
        j.at("id").get<std::string>(),
        j.at("description").get<std::string>(),
        stringToPriority(j.at("priority").get<std::string>()),
        j.at("deadline").get<std::string>(),
        stringToStatus(j.at("status").get<std::string>())
    };  
}
