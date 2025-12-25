# ToDo-CLI

A simple and extensible **command-line ToDo application** written in **C++17** using **modern CMake**.

---

## Features

* Add, list, complete, and remove tasks
* Task priorities: `low`, `medium`, `high`
* Persistent storage in a text file
* Colored terminal output based on priority
* Modular architecture (core library + CLI)
* Unit tests for core logic
* Modern CMake (C++17)

---

## Project Structure

```
ToDo-CLI/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   └── app/
│       ├── Application.cpp
│       ├── Task.cpp
│       ├── TaskManager.cpp
│       ├── cli/
│       │   └── CommandHandler.cpp
│       └── utils/
│           ├── FileHandler.cpp
│           ├── Parser.cpp
│           └── TerminalColors.h
├── tests/
│   ├── test_task.cpp
│   └── test_task_manager.cpp
└── data/
```

---

## Requirements

* CMake >= 3.16
* C++ compiler with C++17 support (GCC / Clang)
* Linux or macOS (Windows via WSL)

---

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Run

```bash
./todo-cli
```

---

## Usage

### Help

```bash
./todo-cli
./todo-cli help
```

### Add task

```bash
./todo-cli add "Learn CMake" high 2025-12-31
```

### List tasks

```bash
./todo-cli list
```

### Mark task as done

```bash
./todo-cli done 1
```

### Remove task

```bash
./todo-cli remove 1
```

---

## Data format

Tasks are stored in a text file using the following format:

```
id|description|priority|deadline|status
```

Example:

```
1|Learn CMake|high|2025-12-31|pending
```

---

## Tests

Build produces two test executables:

* `test_task`
* `test_task_manager`

Run them manually:

```bash
./test_task
./test_task_manager
```

Or via CTest:

```bash
ctest
```

---

## Design

* Core logic is built as a static library (`todo_core`)
* CLI depends only on the core library
* File I/O and parsing are isolated
* No global state
* Easy to extend with new commands

---

## License

MIT License
