#include "UserDatagramProtocol.h"
#define     DEFAULT_PORT    (0xFFFF)
#define     BEGIN_PACKET_FAIL_VALUE         (0)
#define     BEGIN_PACKET_SUCCESS_VALUE      (1)
#define     END_PACKET_FAIL_VALUE           (0)
#define     END_PACKET_SUCCESS_VALUE        (1)

/**
* @brief default constructor.
*/
UserDatagramProtocol::UserDatagramProtocol(): EthernetBase()
{
    this->initialize();
}

/**
* @brief constructor of ethernet with 1 args.
* @param[in] mac_address mac address.
*/
UserDatagramProtocol::UserDatagramProtocol(BYTE* mac_address) :EthernetBase(mac_address)
{
    this->initialize();
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
UserDatagramProtocol::UserDatagramProtocol(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6) :EthernetBase(octet1, octet2, octet3, octet4, octet5, octet6)
{
    this->initialize();
}

UserDatagramProtocol::~UserDatagramProtocol()
{
}

/**
* @brief initialize members
*/
void UserDatagramProtocol::initialize()
{
    this->m_read_port = DEFAULT_PORT;
}

/**
* @brief begin communication.
* @param[in] sspin the pin number of cs pin.
* @return result to begin.
* @retval SUCCESS successful to begin.
* @retval FAIL fail to begin.
* @note if not set ip address and mac address, not begin communication.
*/
RESULT UserDatagramProtocol::beginCommunication()
{
    RESULT result = FAIL;
    
    // call begin method.
    if(EthernetBase::beginCommunication())
    {
        // if successful call begin method.
        if(1 == this->m_ethernet_udp.begin(this->m_read_port))
        {
            //NOTE: if return "1", when success calling begin method.
            //NOTE: if return "0", when fail calling begin method
            result = SUCCESS;
        }
    }
    return result;
}
#include "stdint.h"
#include "stddef.h"

/**
* @brief send data to address.
* @param[in] data data to send.
* @param[in] send_address address to send.
* @param[in] address_size size of send address.
* @return result to send.
* @retval SUCCESS successful to send.
* @retval FAIL fail to send.
*/
RESULT UserDatagramProtocol::sendData(Message_if* data, WORD* send_address, SIZE_T address_size)
{
    RESULT result = SUCCESS;
    WORD port_number = this->getPortNumberFromAddressArray(send_address, address_size);
    IpAddress ip_address;

    //TODO: version 6 support.
    this->getIpAddressFromAddressArray(send_address, address_size, &ip_address, EthernetBase::IpAddress::VERSION::VERSION4);

    // call beginPacket method.
    if(BEGIN_PACKET_SUCCESS_VALUE == this->m_ethernet_udp.beginPacket(*(ip_address.getArduinoClass()), port_number))
    {
        // call write method when beginPacket method return success value.
        this->m_ethernet_udp.write(data->getData_uint8(), data->getDataSize_sizet_uint8());
    }
    else
    {
        // if endPacket method return fail value, result set to fail.
        result = FAIL;
    }

    // call endPacket method.
    if(END_PACKET_SUCCESS_VALUE != this->m_ethernet_udp.endPacket())
    {
        result = FAIL;
    }

    return result;
}

/**
* @brief end communication.
* @return result to end.
* @retval SUCCESS successful to end.
* @retval FAIL fail to end.
*/
RESULT UserDatagramProtocol::endCommunication()
{
    RESULT result = FAIL;
    this->m_ethernet_udp.stop();

    result = SUCCESS;
    return result;
}

/**
* @brief get read port.
* @return the read port .
*/
WORD UserDatagramProtocol::getReadPort()
{
    return this->m_read_port;
}

/**
* @brief set read port.
* @param[in] port read port.
*/
void UserDatagramProtocol::setReadPort(WORD port)
{
    this->m_read_port = port;
}