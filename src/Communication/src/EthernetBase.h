#ifndef _ETHERNET_BASE_H_
#define _ETHERNET_BASE_H_

#include "Communicator_if.h"

/**
* @class EthernetBase
* @brief ethernet base class.
*/
class EthernetBase : public Communicator_if
{
public:
    EthernetBase(BYTE* macAddress){};
    virtual ~EthernetBase(){};
    virtual RESULT sendData(const Message_if* data, DWORD size){return FAIL;};
    virtual RESULT receiveData(Message_if* data, DWORD* size){return FAIL;};

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
    private:
        void setVersion(VERSION version);
        void changeVersion(VERSION version);

        VERSION m_version;
        BYTE* m_address;
    };
    
    virtual void setIpAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4);
    virtual const IpAddress* getIpAddress(void);

protected:
    IpAddress m_ip_address;
};
#endif // _ETHERNET_BASE_H_