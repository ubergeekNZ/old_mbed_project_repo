/* In this example LED1 is switched on/off using a web browser connected to this HTTP server.
 * The example is based on the Tuxgraphics Web Switch <http://www.tuxgraphics.org/>.
 * This HTTP server is built around the the ENC28J60 chip 
 * driven by the UIPEthernet library <https://github.com/ntruchsess/arduino_uip>
 * ported to mbed.
 */

#include <mbed.h>
#include <UIPEthernet.h>
#include <UIPServer.h>
#include <UIPClient.h>
#include <string>

using namespace std;

#define TARGET_NUCLEO_F411RE

// UIPEthernet is the name of a global instance of UIPEthernetClass.
// Do not change the name! It is used within the UIPEthernet library.
#if defined(TARGET_LPC1768)
UIPEthernetClass UIPEthernet(p11, p12, p13, p8);        // mosi, miso, sck, cs
#elif defined(TARGET_LPC1114)
UIPEthernetClass UIPEthernet(dp2, dp1, dp6, dp25);      // mosi, miso, sck, cs
#elif defined(TARGET_LPC11U68)
UIPEthernetClass UIPEthernet(P0_9, P0_8, P1_29, P0_2);  // mosi, miso, sck, cs
#elif defined (TARGET_NUCLEO_F103RB)
UIPEthernetClass UIPEthernet(PB_5, PB_4, PB_3, PB_6);   // mosi, miso, sck, cs
#elif defined (TARGET_NUCLEO_F401RE)
UIPEthernetClass UIPEthernet(PB_5, PB_4, PB_3, PB_6);   // mosi, miso, sck, cs
#elif defined (TARGET_NUCLEO_F411RE)
UIPEthernetClass UIPEthernet(PB_5, PB_4, PB_3, PB_6);   // mosi, miso, sck, cs

// If your board/plaform is not present yet then uncomment the following two lines and replace TARGET_YOUR_BOARD as appropriate.

//#elif defined (TARGET_YOUR_BOARD)
//UIPEthernetClass UIPEthernet(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS);   // mosi, miso, sck, cs

#endif

// Note:
// If it happends that any of the SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS pins collide with LED1 pin
// then either use different SPI port (if available on the board) and change the pin names in the constructor UIPEthernet(...) accordingly
// or instead of using LED1 pin, select a free pin (not used by SPI port) and connect to it an external LED which is connected to a resitor that is connected to the groud.
// In the second case remember to replace LED1 in sw(LED1) constructor (see below).


// MAC number must be unique within the connected network. Modify as appropriate.
const uint8_t    MY_MAC[6] = {0x00,0x01,0x02,0x03,0x04,0x06};
// IP address must be also unique and compatible with your network. Change as appropriate.
const IPAddress  MY_IP(192,168,1,181);
const uint16_t   MY_PORT = 80;      // for HTTP connection
EthernetServer   myServer = EthernetServer(MY_PORT);
// In this example we are turning on/off LED1.
DigitalOut       sw(LED1);  // Change LED1 to a pin of your choice. However, make sure that it does not collide with any of the SPI pins already used in the UIPEthernet(...) constructor above!

const string PASSWORD     = "secret";   // change as you like
const string HTTP_OK      = "HTTP/1.0 200 OK";
const string MOVED_PERM   = "HTTP/1.0 301 Moved Permanently\r\nLocation: ";
const string UNAUTHORIZED = "HTTP/1.0 401 Unauthorized";
string       httpHeader;     // HTTP header
string       httpContent;    // HTTP content


// analyse the url given
// return values: -1 invalid password
//                -2 no command given but password valid
//                -3 just refresh page
//                 0 switch off
//                 1 switch on
//
//                The string passed to this function will look like this:
//                GET /password HTTP/1.....
//                GET /password/ HTTP/1.....
//                GET /password/?sw=1 HTTP/1.....
//                GET /password/?sw=0 HTTP/1.....

int8_t analyse_get_url(string& str)
{
    if(str.substr(5, PASSWORD.size()) != PASSWORD)
        return(-1);

    uint8_t pos = 5 + PASSWORD.size();

    if(str.substr(pos, 1) == " ")
        return(-2);

    if(str.substr(pos, 1) != "/")
        return(-1);

    pos++;

    string cmd(str.substr(pos, 5));

    if(cmd == "?sw=0")
        return(0);

    if(cmd == "?sw=1")
        return(1);

    return(-3);
}

string& moved_perm(uint8_t flag)
{
    if(flag == 1)
        httpContent = "/" +  PASSWORD + "/";
    else
        httpContent = "";

    httpContent += "<h1>301 Moved Permanently</h1>\r\n";

    return (httpContent);
}

string& page(uint8_t status)
{
    httpContent = "<h2>Web Switch</h2>\r\n";

    if(status == 1) {
        httpContent += "<pre>\r\n  <font color=#FF0000>ON</font>";
        httpContent += " <a href=\"./?sw=0\">[switch off]</a>\r\n";
    } else {
        httpContent += "<pre>\r\n  <font color=#00FF00>OFF</font>";
        httpContent += " <a href=\"./?sw=1\">[switch on]</a>\r\n";
    }

    httpContent += "  <a href=\".\">[refresh status]</a>\r\n";
    httpContent += "</pre>\r\n";
    httpContent += "<hr>\r\n";
    return httpContent;
}

void http_send(EthernetClient& client, string& header, string& content)
{
    char content_length[5] = {};

    header += "\r\nContent-Type: text/html\r\n";
    header += "Content-Length: ";
    sprintf(content_length, "%d", content.length());
    header += string(content_length) + "\r\n";
    header += "Pragma: no-cache\r\n";
    header += "Connection: About to close\r\n";
    header += "\r\n";
    string webpage = header + content;
    client.write((uint8_t*)webpage.c_str(),webpage.length());
}

int main()
{
    UIPEthernet.begin(MY_MAC,MY_IP);
    myServer.begin();
    while(1) {
        EthernetClient client = myServer.available();
        if (client) {
            size_t size = client.available();
            if(size > 0) {
                uint8_t* buf = (uint8_t*)malloc(size);
                size = client.read(buf, size);
                string received((char*)buf);
                free(buf);
                if(received.substr(0, 3) != "GET") {
                    // head, post or other method
                    // for possible status codes see:
                    // http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
                    httpHeader = HTTP_OK;
                    httpContent = "<h1>200 OK</h1>";
                    http_send(client, httpHeader, httpContent);
                    continue;
                }

                if(received.substr(0, 6) == "GET / ") {
                    httpHeader = HTTP_OK;
                    httpContent = "<p>Usage: http://host_or_ip/password</p>\r\n";
                    http_send(client, httpHeader, httpContent);
                    continue;
                }

                int cmd = analyse_get_url(received);

                if(cmd == -2) {
                    // redirect to the right base url
                    httpHeader = MOVED_PERM;
                    http_send(client, httpHeader, moved_perm(1));
                    continue;
                }

                if(cmd == -1) {
                    httpHeader = UNAUTHORIZED;
                    httpContent = "<h1>401 Unauthorized</h1>";
                    http_send(client, httpHeader, httpContent);
                    continue;
                }

                if(cmd == 1) {
                    sw = 1;     // switch on
                }

                if(cmd == 0) {
                    sw = 0;    // switch off
                }

                httpHeader = HTTP_OK;
                http_send(client, httpHeader, page(sw));
            }
        }
    }
}


