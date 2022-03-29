#ifndef NULLCOMMANDHANDLER_H_
#define NULLCOMMANDHANDLER_H_

#include "ICommandHandler.h"

// Null object used to terminate chain of responsibility
class NullCommandHandler : public ICommandHandler
{
public:
    NullCommandHandler() : ICommandHandler(*this) {}
    NullCommandHandler(ICommandHandler &handler) : ICommandHandler(*this) {}

    virtual void handle_command(char command_string[], char arg_string[])
    {
        // Do nothing
    }
};

#endif // NULLCOMMANDHANDLER_H_