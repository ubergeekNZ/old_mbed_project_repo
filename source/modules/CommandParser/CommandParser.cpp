#include "CommandParser.h"
#include <string.h>

CommandParser::CommandParser(IComms &comms, IQueue<sEvent>& queue, const CommandArgs cmd[], uint32_t cmd_size)
    : m_comm(comms), m_queue(queue), m_cmd(cmd), m_cmd_size(cmd_size), m_cmdLength(0)
{
    memset(m_cmdString, 0, sizeof(m_cmdString));
}

void CommandParser::ProcessMessages(void)
{
    while (m_comm.new_data_received())
    {
        char newCh = m_comm.get_received_data();

        if (newCh == '\r')
        {
            char *cmdStart = strtok(m_cmdString, ":");
            char *argStart = strtok(NULL, ":");
            const CommandArgs *cmd_ptr = m_cmd;
            for (uint32_t index = 0; index < m_cmd_size; index++)
            {
                if (strcmp(cmdStart, m_cmd->command_string) == 0)
                {
                    // post event
                    event.id = m_cmd->event;
                    // TODO: use a memory pool then we won't have to do this
                    // - a static size array
                    memcpy(m_valueString, argStart, sizeof(m_valueString));
                    event.data = m_valueString;
                    m_queue.enqueue(event);
                    break;
                }
                m_cmd++;
            }

            m_cmd = cmd_ptr;
            m_cmdLength = 0;
            memset(m_cmdString, 0, sizeof(m_cmdString));
            continue;
        }

        if (newCh == '\b')
        {
            m_cmdLength--;

            continue;
        }

        if (m_cmdLength < MAX_COMMAND_STRING)
        {
            m_cmdString[m_cmdLength++] = newCh;
        }
        else
        {
            // wrap over
            m_cmdLength = 0;
        }
    }
}