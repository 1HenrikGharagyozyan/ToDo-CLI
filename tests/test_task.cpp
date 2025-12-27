#include "../src/app/Task.h"
#include "../src/app/utils/Uuid.h"
#include <cassert>
#include <iostream>

int main()
{
    std::string id = generateUuid();
    Task t(id, "Learn Linux", Priority::HIGH, "2025-12-25", Status::PENDING);

    // Checking getters
    assert(t.getId() == id);
    assert(t.getDescription() == "Learn Linux");
    assert(t.getPriority() == Priority::HIGH);
    assert(t.getDeadline() == "2025-12-25");
    assert(t.getStatus() == Status::PENDING);

    // Checking serialization / deserialization
    std::string serialized = t.serialize();
    Task t2 = Task::deserialize(serialized);
    assert(t2.getId() == t.getId());
    assert(t2.getDescription() == t.getDescription());

    // Checking toString() (output to terminal)
    std::cout << t.toString() << std::endl;

    std::cout << "All Task tests passed!" << std::endl;
    return 0;
}
