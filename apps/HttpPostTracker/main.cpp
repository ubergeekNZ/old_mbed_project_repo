#include "mbed.h"
#include "WIZnetInterface.h"
#include "HTTPClient.h"

#include "Events.h"
#include "Queue.h"
#include "GridEye.h"
#include "SystemTime.h"
#include "Tracker.h"
 
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
// 

#define USART_1_TX     PA_9
#define USART_1_RX     PA_10

Serial pc(USART_1_TX, USART_1_RX);
 
// MOSI, MISO, SCK
SPI spi(PA_7,PA_6,PA_5);

// spi, cs and reset
// WIZnetInterface ethernet(&spi,PA_4,PC_4);

WIZnetInterface ethernet(&spi,PA_4,PD_2);
 
#define EVENT_QUEUE_SIZE    (20)
Queue<sEvent> event_queue(EVENT_QUEUE_SIZE);
GridEye therm_sensor(PB_7, PB_6);
SystemTime sys_timer;
Tracker track_object(sys_timer, therm_sensor, event_queue);


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
    char nameYouWant[] = "peopleCounting";
    while(1)
    {   
        track_object.ProcessTracker();

        if (!event_queue.isEmpty())
        {
            sEvent event = event_queue.dequeue();

            if (event.id == EVT_SEND_COUNTER)
            {
                uint32_t up_counter = track_object.read_up_counter();
                uint32_t down_counter = track_object.read_down_counter();

                sprintf(get_msg,"http://dweet.io/dweet/for/%s?up=%d&down=%d",nameYouWant,(int)up_counter, (int)down_counter);
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
                // pc.printf("Tracker - Up: %03d Down: %03d\n", up_counter, down_counter);
            }
        }

    }
   
}