#include "EthernetBase.h"
#include <MemoryUtility.h>
#include <Ethernet.h>

const BYTE EthernetBase::MAC_ADDRESS_SIZE = 6;

/**
* @brief default constructor.
*/
EthernetBase::IpAddress::IpAddress()
{
    this->m_version = VERSION::NONE_VERSION;
    this->m_address = nullptr;
    this->m_arduino_ipaddress = nullptr;
}

/**
* @brief destructor.
*/
EthernetBase::IpAddress::~IpAddress()
{
    delete[] this->m_address;
    this->freeArduinoClass();
}

/**
* @brief constructor of ip address in version 4.
* @param[in] octet1 first octet of the ip address.
* @param[in] octet2 second octet of the ip address.
* @param[in] octet3 third octet of the ip address.
* @param[in] octet4 fourth octet of the ip address.
*/
EthernetBase::IpAddress::IpAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4) : IpAddress()
{
    this->setAddress(octet1, octet2, octet3, octet4);
}

/**
* @brief constructor of ip address in version 6.
* @param[in] octet1 first octet of the ip address.
* @param[in] octet2 second octet of the ip address.
* @param[in] octet3 third octet of the ip address.
* @param[in] octet4 fourth octet of the ip address.
* @param[in] octet5 fifth octet of the ip address.
* @param[in] octet6 sixth octet of the ip address.
*/
EthernetBase::IpAddress::IpAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6) : IpAddress()
{
    this->setAddress(octet1, octet2, octet3, octet4, octet5, octet6);
}

/**
* @brief return the version of the ip address.
* @return the version of the ip address.
*/
EthernetBase::IpAddress::VERSION EthernetBase::IpAddress::getVersion(void)
{
    return this->m_version;
}

/**
* @brief return the size of the ip address.
* @return address size.
*/
BYTE EthernetBase::IpAddress::getAddressSize(void)
{
    return this->m_version;
}

/**
* @brief return the address.
* @return ip address.
* @note if did not set ip address, return nullptr.
*/
BYTE* EthernetBase::IpAddress::getAddress(void)
{
    return this->m_address;
}

/**
* @brief set the address.
* @details if already set address, free the address.
* @param[in] octet1 first octet of the ip address.
* @param[in] octet2 second octet of the ip address.
* @param[in] octet3 third octet of the ip address.
* @param[in] octet4 fourth octet of the ip address.
*/
void EthernetBase::IpAddress::setAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4)
{
    this->setVersion(VERSION::VERSION4);
    
    // set address.
    this->m_address[0] = octet1;
    this->m_address[1] = octet2;
    this->m_address[2] = octet3;
    this->m_address[3] = octet4;
    
    this->setArduinoClass();
}

/**
* @brief set the address.
* @details if already set address, free the address.
* @param[in] octet1 first octet of the ip address.
* @param[in] octet2 second octet of the ip address.
* @param[in] octet3 third octet of the ip address.
* @param[in] octet4 fourth octet of the ip address.
* @param[in] octet5 fifth octet of the ip address.
* @param[in] octet6 sixth octet of the ip address.
*/
void EthernetBase::IpAddress::setAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6)
{
    this->setVersion(VERSION::VERSION6);

    // set address.
    this->m_address[0] = octet1;
    this->m_address[1] = octet2;
    this->m_address[2] = octet3;
    this->m_address[3] = octet4;
    this->m_address[4] = octet5;
    this->m_address[5] = octet6;

    this->setArduinoClass();
}

/**
* @brief get the Arduino class.
*/
IPAddress* EthernetBase::IpAddress::getArduinoClass()
{
    return this->m_arduino_ipaddress;
}

/**
* @brief set the Arduino class.
* @note Unimplemented version 6.
*/
void EthernetBase::IpAddress::setArduinoClass()
{
    this->freeArduinoClass();
    switch(this->m_version)
    {
        // ip address version 4.
        case VERSION::VERSION4:
            this->m_arduino_ipaddress = new IPAddress(this->m_address[0], this->m_address[1], this->m_address[2], this->m_address[3]);
            break;
        default:
            break;
    }
}

/**
* @brief free the Arduino class.
*/
void EthernetBase::IpAddress::freeArduinoClass()
{
    delete this->m_arduino_ipaddress;
    this->m_arduino_ipaddress = nullptr;
}

/**
* @brief set the version.
* @details if the current version is different version, call change version method.
* @param[in] version the version to set.
*/
void EthernetBase::IpAddress::setVersion(VERSION version)
{
    // if current address is different version, free the address.
    if(version != this->m_version)
    {
        this->m_version = version; // set the version.
        this->changeVersion(version);
    }
}

/**
* @brief change the version.
* @param[in] version the version of changed.
*/
void EthernetBase::IpAddress::changeVersion(VERSION version)
{
    delete[] this->m_address; // delete the current address.
    this->m_address = new BYTE[this->getAddressSize()]; // allocate address array.
}


// ======================
// ===  EthernetBase  ===
// ======================


/**
* @brief default constructor.
*/
EthernetBase::EthernetBase()
{
    this->m_ip_address = nullptr;
    this->m_is_need_ip_address_delete = FALSE;
    this->m_cs_pin_no = HARDWARE_CSPIN::NONE_HARDWARE;
    this->m_mac_address = new BYTE[this->MAC_ADDRESS_SIZE];
    MemoryUtility::memClear(this->m_mac_address, this->MAC_ADDRESS_SIZE);
}

/**
* @brief destructor.
*/
EthernetBase::~EthernetBase()
{
    this->freeIpAddress();
    delete[] this->m_mac_address;
}

/**
* @brief begin communication.
* @param[in] sspin the pin number of cs pin.
* @return result to begin.
* @retval SUCCESS successful to begin.
* @retval FAIL fail to begin.
* @note if not set ip address and mac address, not begin communication.
*/
RESULT EthernetBase::begin()
{
    RESULT result = FAIL;
    if(nullptr != this->m_ip_address)
    {
        Ethernet.init(this->m_cs_pin_no);
        Ethernet.begin(this->m_mac_address, *(this->m_ip_address->getArduinoClass()));
        if( (EthernetHardwareStatus::EthernetNoHardware != Ethernet.hardwareStatus()) && 
            (EthernetLinkStatus::LinkOFF != Ethernet.linkStatus()))
        {
            result = SUCCESS;
        }
    }
    return result;
}

/**
* @brief constructor of ethernet with 1 args.
* @param[in] mac_address mac address.
*/
EthernetBase::EthernetBase(BYTE* mac_address) : EthernetBase()
{
    this->setMacAddress(mac_address);
}

/**
* @brief constructor of ethernet with 6 args.
* @param[in] octet1 first octet of the mac address.
* @param[in] octet2 second octet of the mac address.
* @param[in] octet3 third octet of the mac address.
* @param[in] octet4 fourth octet of the mac address.
* @param[in] octet5 fifth octet of the mac address.
* @param[in] octet6 sixth octet of the mac address.
*/
EthernetBase::EthernetBase(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6) : EthernetBase()
{
    this->setMacAddress(octet1, octet2, octet3, octet4, octet5, octet6);
}

/**
* @brief return mac address.
*/
BYTE* EthernetBase::getMacAddress()
{
    return this->m_mac_address;
}

/**
* @brief return mac address.
* @param[out] mac_address set the mac address of this object.
*/
void EthernetBase::getMacAddress(BYTE* mac_address)
{
    if(nullptr != mac_address)
    {
        for(WORD i = 0; i < this->MAC_ADDRESS_SIZE; i++)
        {
            mac_address[i] = this->m_mac_address[i];
        }
    }
}

/**
* @brief set mac address.
* @param[in] mac_address the mac address to set.
*/
void EthernetBase::setMacAddress(BYTE* mac_address)
{
    if(nullptr != mac_address)
    {
        MemoryUtility::memCopy(this->m_mac_address, mac_address, this->MAC_ADDRESS_SIZE);
    }
}

/**
* @brief set mac address by args.
* @param[in] octet1 first octet of the mac address.
* @param[in] octet2 second octet of the mac address.
* @param[in] octet3 third octet of the mac address.
* @param[in] octet4 fourth octet of the mac address.
* @param[in] octet5 fifth octet of the mac address.
* @param[in] octet6 sixth octet of the mac address.
*/
void EthernetBase::setMacAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6)
{
    this->m_mac_address[0] = octet1;
    this->m_mac_address[1] = octet2;
    this->m_mac_address[2] = octet3;
    this->m_mac_address[3] = octet4;
    this->m_mac_address[4] = octet5;
    this->m_mac_address[5] = octet6;
}

/**
* @brief set ip address.
* @note ip_address do not clone.
* @param[in] ip_address IpAddress object.
*/
void EthernetBase::setIpAddress(EthernetBase::IpAddress* ip_address)
{
    this->freeIpAddress();
    this->m_ip_address = ip_address;
}

/**
* @brief set ip address.
* @param[in] octet1 first octet of the ip address.
* @param[in] octet2 second octet of the ip address.
* @param[in] octet3 third octet of the ip address.
* @param[in] octet4 fourth octet of the ip address.
*/
void EthernetBase::setIpAddress(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4)
{
    if(nullptr == this->m_ip_address)
    {
        this->m_ip_address = new IpAddress(octet1, octet2, octet3, octet4);
        this->m_is_need_ip_address_delete = TRUE;
    }
    else
    {
        this->m_ip_address->setAddress(octet1, octet2, octet3, octet4);
    }
}

/**
* @brief get ip address.
* @return struct of the ip address.
*/
EthernetBase::IpAddress* EthernetBase::getIpAddress(void)
{
    return this->m_ip_address;
}


void EthernetBase::freeIpAddress()
{
    if(TRUE == this->m_is_need_ip_address_delete)
    {
        delete this->m_ip_address;
        this->m_ip_address = nullptr;
        this->m_is_need_ip_address_delete = FALSE;
    }
}

/**
* @brief return cs pin No.
*/
BYTE EthernetBase::getCsPinNo()
{
    return this->m_cs_pin_no;
}

/**
* @brief set cs pin No.
*/
void EthernetBase::setCsPinNo(BYTE cs_pin)
{
    this->m_cs_pin_no = cs_pin;
}