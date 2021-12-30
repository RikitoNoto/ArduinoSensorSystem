#ifndef _ETHERNET_UDP_H_
#define _ETHERNET_UDP_H_
#include <stdint.h>
#include <stddef.h>
#include "Ethernet.h"

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

	virtual void stop() // Finish with the UDP socket
    {
        EthernetUDP::is_called_stop = true;
    }
    
	virtual int beginPacket(IPAddress ip, uint16_t port)
    {
        EthernetUDP::is_called_beginPacket = true;
        return EthernetUDP::return_beginPacket;
    }

	virtual size_t write(const uint8_t *buffer, size_t size)
    {
        EthernetUDP::is_called_write = true;
        return 0;
    }

	// Finish off this packet and send it
	// Returns 1 if the packet was sent successfully, 0 if there was an error
	virtual int endPacket()
    {
        EthernetUDP::is_called_endPacket = true;
        return EthernetUDP::return_endPacket;
    }

    static void setUp()
    {
        EthernetUDP::is_called_begin = false;
        EthernetUDP::is_called_stop = false;
        EthernetUDP::is_called_beginPacket = false;
        EthernetUDP::is_called_write = false;
        EthernetUDP::is_called_endPacket = false;
        EthernetUDP::begin_arg_port_no = 0xFFFF;
        EthernetUDP::return_begin = 1;
        EthernetUDP::return_beginPacket = 1;
        EthernetUDP::return_endPacket = 1;
    }

    static int return_beginPacket;
    static int return_endPacket;
    static uint8_t return_begin;
    static uint16_t begin_arg_port_no;
    static bool is_called_begin;
    static bool is_called_stop;
    static bool is_called_beginPacket;
    static bool is_called_write;
    static bool is_called_endPacket;
};
#endif // _ETHERNET_UDP_H_