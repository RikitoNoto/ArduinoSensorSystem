#ifndef _ETHERNET_BASE_H_
#define _ETHERNET_BASE_H_

#include "Communicator_if.h"

class IPAddress;

/**
* @class EthernetBase
* @brief ethernet base class.
*/
class EthernetBase : public Communicator_if
{
public:
    EthernetBase();
    EthernetBase(BYTE* mac_address);
    EthernetBase(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6);
    virtual ~EthernetBase();

    // const of cs pin.
    enum HARDWARE_CSPIN: BYTE
    {
        NONE_HARDWARE = 0,
        ARDUINO_SHIELD = 10,
    };

    virtual RESULT begin();
    // virtual RESULT begin(BYTE sspin); // begin communication.
    virtual RESULT sendData(const Message_if* data, DWORD size){return FAIL;};  // send data.
    virtual RESULT receiveData(Message_if* data, DWORD* size){return FAIL;};    // receive data.

    /**
    * @class IpAddress
    * @brief create ip address.
    */
    class IpAddress
    {
    public:
        IpAddress(); // default constructor
        IpAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4); // version4 constructor
        IpAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6); // version6 constructor
        virtual ~IpAddress();

        // const of ip address version
        enum VERSION: BYTE
        {
            NONE_VERSION = 0,
            VERSION4 = 4,
            VERSION6 = 6
        };

        VERSION getVersion(void);   // get version of the ip address.
        BYTE getAddressSize(void);  // get size of the ip address.
        BYTE* getAddress(void);     // get ip address as array of byte.
        void setAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4); // set the ip address of version4.
        void setAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6); // set the ip address of version6.
        IPAddress* getArduinoClass(); // get the Arduino class.

    private:
        void setVersion(VERSION version);       // set version of the ip address.
        void changeVersion(VERSION version);    // call when changed version.
        void setArduinoClass(void);             // set Arduino class.
        void freeArduinoClass(void);            // free Arduino class.

        IPAddress* m_arduino_ipaddress; // arduino ip address class.
        VERSION m_version;  // the version of the ip address.
        BYTE* m_address;    // the ip address as byte array.
    };
    
    virtual void setIpAddress(IpAddress* ip_address);   // set ip address by ip address instance.
    virtual void setIpAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4);
    virtual IpAddress* getIpAddress(void);

    static const BYTE MAC_ADDRESS_SIZE;
    virtual void getMacAddress(BYTE* mac_address);
    virtual BYTE* getMacAddress(void);
    virtual void setMacAddress(BYTE* mac_address);
    virtual void setMacAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6);
    virtual BYTE getCsPinNo(void);
    virtual void setCsPinNo(BYTE cs_pin);

protected:
    void freeIpAddress();

    IpAddress* m_ip_address;
    BYTE* m_mac_address;
    BOOL m_is_need_ip_address_delete;
    BYTE m_cs_pin_no;
};
#endif // _ETHERNET_BASE_H_