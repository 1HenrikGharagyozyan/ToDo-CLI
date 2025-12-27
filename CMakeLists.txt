cmake_minimum_required(VERSION 3.16)

project(ToDoCLI
    VERSION 1.0
    LANGUAGES CXX
)

# =========================
# C++ standard
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# =========================
# Core library
# =========================
add_library(todo_core
    src/app/Task.cpp
    src/app/TaskManager.cpp
    src/app/utils/FileHandler.cpp
    src/app/utils/Parser.cpp
    src/app/utils/Uuid.cpp
)

target_include_directories(todo_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)


target_compile_options(todo_core
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# =========================
# Dependencies
# =========================
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(todo_core
    PUBLIC
        nlohmann_json::nlohmann_json
)


# =========================
# CLI executable
# =========================
add_executable(todo-cli
    src/main.cpp
    src/app/Application.cpp
    src/app/cli/CommandHandler.cpp
)

target_link_libraries(todo-cli
    PRIVATE
        todo_core
)

target_compile_options(todo-cli
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# =========================
# Tests
# =========================
enable_testing()

add_executable(test_task
    tests/test_task.cpp
)
target_link_libraries(test_task PRIVATE todo_core)

add_executable(test_task_manager
    tests/test_task_manager.cpp
)
target_link_libraries(test_task_manager PRIVATE todo_core)

add_test(NAME TaskTests COMMAND test_task)
add_test(NAME TaskManagerTests COMMAND test_task_manager)

# =========================
# Install
# =========================
install(TARGETS todo-cli
    RUNTIME DESTINATION bin
)
