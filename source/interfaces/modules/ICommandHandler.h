#ifndef ICOMMANDHANDLER_H_
#define ICOMMANDHANDLER_H_

// Uses a chain of responsibility pattern to handle serial commands
class ICommandHandler
{
protected:
    ICommandHandler &_successor;
public:
    ICommandHandler(ICommandHandler &handler) : _successor(handler) {}
    virtual ~ICommandHandler() {}
    virtual void handle_command(char command_string[], char arg_string[])
    {
        _successor.handle_command(command_string, arg_string);
    }
};

#endif // ICOMMANDHANDLER_H_