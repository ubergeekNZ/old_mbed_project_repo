#ifndef CMD_PARSER_H_
#define CMD_PARSER_H_

#include "IQueue.h"
#include "IComms.h"
#include "Types.h"
#include "Events.h"
#include "stdint.h"

#define MAX_COMMAND_STRING		(64)
#define MAX_DATA_BUFFER	(20)

// Unwraps received messages into command name and parameters
class CommandParser
{
private:
    IComms &m_comm;
    IQueue<sEvent>& m_queue;
    const CommandArgs *m_cmd;
    uint32_t m_cmd_size;
    uint32_t m_cmdLength;
    char m_cmdString[MAX_COMMAND_STRING];
    sEvent event;
    char m_valueString[MAX_DATA_BUFFER];
public:
    // Inject a publisher for received commands
    CommandParser(IComms &comms, IQueue<sEvent>& queue, const CommandArgs cmd[], uint32_t cmd_size);
    void ProcessMessages(void);
};

#endif // CMD_PARSER_H_