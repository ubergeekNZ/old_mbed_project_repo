#include "mbed.h"
#include "WIZnetInterface.h"
#include "HTTPClient.h"
 
#define USE_DHCP    1
 
const char * IP_Addr    = "192.168.1.65";
const char * IP_Subnet  = "255.255.255.0";
const char * IP_Gateway = "192.168.1.254";
unsigned char MAC_Addr[6] = {0x00,0x08,0xDC,0x12,0x34,0x56};
 
// IP: 192.168.1.65, MASK: 255.255.255.0, GW: 192.168.1.254

// Serial pc(PA_2, PA_3);
// Serial pc(PD_5, PD_6);
// 
// #define USART_1_TX     PB_6
// #define USART_1_RX     PB_7

#define USART_1_TX     PA_9
#define USART_1_RX     PA_10
Serial pc(USART_1_TX, USART_1_RX);
 
// MOSI, MISO, SCK
SPI spi(PA_7,PA_6,PA_5);

// spi, cs and reset
// WIZnetInterface ethernet(&spi,PA_4,PC_4);

WIZnetInterface ethernet(&spi,PA_4,PD_2);
 
int main() {
 
    mbed_mac_address((char *)MAC_Addr); //Use mbed mac addres
    pc.baud(115200);
    #if USE_DHCP
    int ret = ethernet.init(MAC_Addr);
    #else
    int ret = ethernet.init(MAC_Addr,IP_Addr,IP_Subnet,IP_Gateway);
    #endif
    if (!ret) {
        pc.printf("Initialized, MAC: %s\r\n", ethernet.getMACAddress());
        ret = ethernet.connect();
        if (!ret) {
            pc.printf("IP: %s, MASK: %s, GW: %s\r\n",
                      ethernet.getIPAddress(), ethernet.getNetworkMask(), ethernet.getGateway());
        } else {
            pc.printf("Error ethernet.connect() - ret = %d\r\n", ret);
            exit(0);
        }
    } else {
        pc.printf("Error ethernet.init() - ret = %d\r\n", ret);
        exit(0);
    }
    
    char str[512];
    char get_msg[128]= "";
    
    /*
        http://dweet.io/follow/nameYouWant
    */
    char nameYouWant[] = "nameYouWant";
    while(1)
    {   

        sprintf(get_msg,"http://dweet.io/dweet/for/%s?a0=%d",nameYouWant,(int)(rand()/1000));
        HTTPClient http;
        
        pc.printf("Send post message to dweet.io\r\n");
        pc.printf("msg : %s\r\n",get_msg);
        ret = http.get(get_msg, str, sizeof(str));
        if(!ret)
        {
          pc.printf("\r\nPage fetched successfully - read %d characters\r\n", strlen(str));
          pc.printf("Result: %s\r\n", str);
        }
        else
        {
          pc.printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
        }
        wait(5);
    }
   
}