#include "../src/app/TaskManager.h"
#include "../src/app/utils/Uuid.h"
#include <cassert>
#include <iostream>

int main() 
{
    TaskManager manager;

    Task t1(generateUuid(), "Learn Linux", Priority::HIGH, "2025-12-25", Status::PENDING);
    Task t2(generateUuid(), "Buy groceries", Priority::MEDIUM, "2025-12-26", Status::DONE);

    manager.addTask(t1);
    manager.addTask(t2);

    assert(manager.listTasks().size() == 2);

    // Проверка поиска
    assert(manager.findTask(t1.getId())->getDescription() == "Learn Linux");
    assert(manager.findTask("nonexistent") == nullptr);

    // Удаление
    assert(manager.removeTask(t1.getId()) == true);
    assert(manager.listTasks().size() == 1);

    // Сохранение и загрузка
    manager.saveToFile("test_tasks.json");
    TaskManager newManager;
    newManager.loadFromFile("test_tasks.json");
    assert(newManager.listTasks().size() == 1);
    assert(newManager.listTasks()[0].getDescription() == "Buy groceries");

    std::cout << "All TaskManager tests passed!" << std::endl;
    return 0;
}
