#include "EthernetBase.h"
#include <MemoryUtility.h>

const BYTE EthernetBase::MAC_ADDRESS_SIZE = 6;

/**
* @brief default constructor.
*/
EthernetBase::IpAddress::IpAddress()
{
    this->m_version = VERSION::NONE_VERSION;
    this->m_address = nullptr;
}

/**
* @brief destructor.
*/
EthernetBase::IpAddress::~IpAddress()
{
    delete[] this->m_address;
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
    this->m_mac_address = new BYTE[this->MAC_ADDRESS_SIZE];
    MemoryUtility::memclear(this->m_mac_address, this->MAC_ADDRESS_SIZE);
}

/**
* @brief destructor.
*/
EthernetBase::~EthernetBase()
{
    delete this->m_ip_address;
    delete[] this->m_mac_address;
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
        for(WORD i = 0; i < this->MAC_ADDRESS_SIZE; i++)
        {
            this->m_mac_address[i] = mac_address[i];
        }
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
* @param[in] ip_address IpAddress object.
*/
void EthernetBase::setIpAddress(EthernetBase::IpAddress* ip_address)
{
    delete this->m_ip_address;
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