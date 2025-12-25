#pragma once
#include <string>
#include <iostream>
#include <sstream>

#include "utils/TerminalColors.h"

enum class Priority { LOW, MEDIUM, HIGH };
enum class Status { PENDING, DONE };

class Task 
{
public:
    // Конструкторы
    Task() = default;
    Task(int id, const std::string& desc, Priority prio, const std::string& deadline, Status st);

    // Геттеры
    int getId() const;
    std::string getDescription() const;
    Priority getPriority() const;
    std::string getDeadline() const;
    Status getStatus() const;

    // Сеттеры
    void setDescription(const std::string& desc);
    void setPriority(Priority prio);
    void setDeadline(const std::string& deadline);
    void setStatus(Status st);

    // Методы
    std::string toString() const;                // Цветной вывод для CLI
    std::string serialize() const;               // Для записи в файл
    static Task deserialize(const std::string&); // Для чтения из файла

private:
    // Вспомогательные методы для конвертации enum <-> string
    static std::string priorityToString(Priority p);
    static Priority stringToPriority(const std::string& str);

    static std::string statusToString(Status s);
    static Status stringToStatus(const std::string& str);

private:
    int id;
    std::string description;
    Priority priority;
    std::string deadline; // YYYY-MM-DD
    Status status;

};
