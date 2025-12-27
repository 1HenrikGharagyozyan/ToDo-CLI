#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

enum class Priority
{
    LOW,
    MEDIUM,
    HIGH
};
enum class Status
{
    PENDING,
    DONE
};

class Task
{
public:
    // Constructors
    Task() = default;
    Task(const std::string &id, const std::string &desc, Priority prio, const std::string &deadline, Status st);

    // Getters
    std::string getId() const;
    std::string getDescription() const;
    Priority getPriority() const;
    std::string getDeadline() const;
    Status getStatus() const;

    // Setters
    void setDescription(const std::string &desc);
    void setPriority(Priority prio);
    void setDeadline(const std::string &deadline);
    void setStatus(Status st);

    // Methods
    std::string toString() const;                 // Colored output for CLI
    std::string serialize() const;                // For writing to file
    static Task deserialize(const std::string &); // For reading from file

    // Methods for JSON serialization
    json toJson() const;
    static Task fromJson(const json &j);

private:
    // Helper methods for enum <-> string conversion
    static std::string priorityToString(Priority p);
    static Priority stringToPriority(const std::string &str);

    static std::string statusToString(Status s);
    static Status stringToStatus(const std::string &str);

private:
    std::string _id; // Unique identifier
    std::string _description;
    Priority _priority;
    std::string _deadline; // YYYY-MM-DD
    Status _status;
};
