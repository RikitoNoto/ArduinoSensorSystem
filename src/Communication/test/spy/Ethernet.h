#ifndef _ETHERNET_H_
#define _ETHERNET_H_
#include <stdint.h>

enum EthernetLinkStatus {
	Unknown,
	LinkON,
	LinkOFF
};

enum EthernetHardwareStatus
{
	EthernetNoHardware,
	EthernetW5100,
	EthernetW5200,
	EthernetW5500
};

class IPAddress
{
public:
    // Constructors
    IPAddress()
    {
        this->spy_address = 0;
    }
    IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) : IPAddress()
    {
        this->spy_address += (first_octet << 24);
        this->spy_address += (second_octet << 16);
        this->spy_address += (third_octet << 8);
        this->spy_address += (fourth_octet);
    }

    IPAddress(uint32_t address)
    {
        this->spy_address = address;
    }
    IPAddress(const uint8_t *address)
    {
        
    }

    uint32_t spy_address;
};

class EthernetClass
{
public:
    EthernetClass()
    {
        this->setUp();
    }

	static void init(uint8_t sspin)
    {
        EthernetClass::isCalledInit = true;
        EthernetClass::cspin = sspin;
    }

	static void begin(uint8_t *mac, IPAddress ip)
    {
        EthernetClass::isCalledBegin = true;
        EthernetClass::spy_mac = mac;
        EthernetClass::spy_ip = ip;
    }

    static void setUp()
    {
        EthernetClass::isCalledInit = false;
        EthernetClass::isCalledBegin = false;
        EthernetClass::spy_mac = nullptr;
        EthernetClass::cspin = 0;
        EthernetClass::return_hardware_value = EthernetHardwareStatus::EthernetW5100;
        EthernetClass::return_link_status = EthernetLinkStatus::LinkON;
    }
    
	static EthernetHardwareStatus hardwareStatus()
    {
        return EthernetClass::return_hardware_value;
    }

	static EthernetLinkStatus linkStatus()
    {
        return EthernetClass::return_link_status;
    }

    static EthernetHardwareStatus return_hardware_value;
    static EthernetLinkStatus return_link_status;
    static uint8_t cspin;
    static bool isCalledInit;
    static bool isCalledBegin;
    static uint8_t* spy_mac;
    static IPAddress spy_ip;

};

extern EthernetClass Ethernet;
#endif // _ETHERNET_H_