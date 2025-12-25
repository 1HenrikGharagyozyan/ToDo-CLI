#include "Parser.h"

Command Parser::parse(int argc, char* argv[])
{
    Command cmd;

    if (argc < 2)
        return cmd;

    cmd.name = argv[1];
    for (int i = 2; i < argc; ++i)
        cmd.args.emplace_back(argv[i]);
    return cmd;
}