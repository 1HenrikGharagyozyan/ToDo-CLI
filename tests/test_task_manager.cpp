#include "../src/app/TaskManager.h"
#include <cassert>
#include <iostream>

int main() 
{
    TaskManager manager;

    Task t1(1, "Learn Linux", Priority::HIGH, "2025-12-25", Status::PENDING);
    Task t2(2, "Buy groceries", Priority::MEDIUM, "2025-12-26", Status::DONE);

    manager.addTask(t1);
    manager.addTask(t2);

    assert(manager.listTasks().size() == 2);

    // Проверка поиска
    assert(manager.findTask(1)->getDescription() == "Learn Linux");
    assert(manager.findTask(3) == nullptr);

    // Удаление
    assert(manager.removeTask(1) == true);
    assert(manager.listTasks().size() == 1);

    // Сохранение и загрузка
    manager.saveToFile("test_tasks.txt");
    TaskManager newManager;
    newManager.loadFromFile("test_tasks.txt");
    assert(newManager.listTasks().size() == 1);
    assert(newManager.listTasks()[0].getDescription() == "Buy groceries");

    std::cout << "All TaskManager tests passed!" << std::endl;
    return 0;
}
