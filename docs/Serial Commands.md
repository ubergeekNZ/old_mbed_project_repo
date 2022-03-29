# Serial Commands

*setrate* - this command sets the poll rate of the thermopile  

    Example - setrate:10 - this set the poll rate to 10 fps

*getrate* - this command get the poll rate of the thermopile in integer  
*setoffset* - this command sets the offset of the thermopile pixel  

    Example - setoffset:0,2.0 - this set the pixel 0 offset to 2.0

*getoffset* - this command get the offset of the thermopile pixel

    Example - getoffset
    Return pixel number (int) and offset value (float).  
    Data starts with '{' and ends with '}'
    {
    0,2.0
    1,2.0
    -
    -
    -
    63,2.3

*getframe* - this command get a frame from the thermopile

    Example - getframe
    Return pixel number (int) and temp value (float)
    Data starts with '{' and ends with '}'
    {
    0,2.0
    1,2.0
    -
    -
    -
    63,2.3

*gettemp* - this command get the thermistor value from the thermopile in float  
*setunitid* - this command sets the id of the unit (32 bit integer)

    Example - setrate:16532 - this sets the id of the unit

*getunitid* - this command get the poll rate of the thermopile in integer   
*setipaddr* - this command sets the id of the unit (32 bit integer)

    Example - setipaddr:1079733050 - this sets the ip address to 64.91.107.58

*getipaddr* - this command get the ip address of the unit in integer 

*setmode* - this command sets the mode (0 - normal, 1 - stop, 2 - stream)

    Example - setmode:0 - this sets the unit to normal operation

*getmode* - this command get the mode of the unit    
*setthresh* - this set the tracker threshold use for detecting peak. Currently default to 2.0f.  

    Example - setthresh:2.0
    
*getthresh* - this command get the tracker threshold of the unit   









