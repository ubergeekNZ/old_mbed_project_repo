#ifndef INC_TYPES_H_
#define INC_TYPES_H_

#define NUMBER_OF_PIXELS	(64)

#include "Events.h"

enum eTimeUnit
{
  TIME_MS = 0,
  TIME_S,
  TIME_MIN,
  TIME_HR  
};

typedef unsigned int TimerId;

typedef struct 
{
    float pixel[NUMBER_OF_PIXELS];
} ImageStruct;


typedef struct
{
    eEvent event;
    const char* command_string;
} CommandArgs;


typedef void (*funcPtr)(void);

#endif 