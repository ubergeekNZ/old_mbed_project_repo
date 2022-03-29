#include "NetworkUtils.h"
#include <cstdio>
#include <cstdlib>
#include "string.h"


uint32_t parseIPV4string(char* ipAddress) {
  uint8_t ipbytes[4];
  char *marker, *ret;
  ret = strtok_r(ipAddress, ".", &marker);
  ipbytes[0] = (unsigned char)strtod(ret, NULL);
  ret = strtok_r(NULL, ".", &marker);
  ipbytes[1] = (unsigned char)strtod(ret, NULL);
  ret = strtok_r(NULL, ".", &marker);
  ipbytes[2] = (unsigned char)strtod(ret, NULL);
  ret = strtok_r(NULL, ".", &marker);
  ipbytes[3] = (unsigned char)strtod(ret, NULL);

  // sscanf(ipAddress, "%uhh.%uhh.%uhh.%uhh", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
  return ipbytes[3] | ipbytes[2] << 8 | ipbytes[1] << 16 | ipbytes[0] << 24;
}

char* getIPV4string(int ip)
{
	static char str_buffer[20];
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;	
    sprintf(str_buffer, "%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]); 
    return str_buffer;    
}