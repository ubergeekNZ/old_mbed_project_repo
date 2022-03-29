#ifndef STATES_H
#define STATES_H

// TODO(Paul) - need to make this into a struct with int

enum eState 
{
  STATE_NORMAL = 0,
  STATE_SENSOR,
  STATE_CONFIGURATION,
  STATE_DIAGNOSTICS,
  STATE_BOOTLOADER,
  STATE_MAX
};
 
#endif // STATES_H
