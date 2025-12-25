#include "Application.h"

#include "TaskManager.h"
#include "utils/Parser.h"
#include "cli/CommandHandler.h"

static const std::string DATA_FILE = "tasks.txt";

int Application::run(int argc, char* argv[])
{
    TaskManager manager;
    manager.loadFromFile(DATA_FILE);

    // Parse command line arguments
    Command cmd = Parser::parse(argc, argv);

    CommandHandler cmdHandler(manager);
    return cmdHandler.handle(cmd);
}