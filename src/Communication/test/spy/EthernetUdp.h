#ifndef _ETHERNET_UDP_H_
#define _ETHERNET_UDP_H_
#include <stdint.h>

class EthernetUDP
{
public:
	EthernetUDP(){}  // Constructor
    
    // initialize, start listening on specified port. Returns 1 if successful, 0 if there are no sockets available to use
	virtual uint8_t begin(uint16_t port)
    {
        EthernetUDP::is_called_begin = true;
        EthernetUDP::begin_arg_port_no = port;
        return EthernetUDP::return_begin;
    }

    static void setUp()
    {
        EthernetUDP::is_called_begin = false;
        EthernetUDP::begin_arg_port_no = 0xFFFF;
        EthernetUDP::return_begin = 1;
    }

    static uint8_t return_begin;
    static bool is_called_begin;
    static uint16_t begin_arg_port_no;
};
#endif // _ETHERNET_UDP_H_