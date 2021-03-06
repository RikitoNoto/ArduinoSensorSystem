#ifndef _USER_DATAGRAM_PROTOCOL_H_
#define _USER_DATAGRAM_PROTOCOL_H_

#include "EthernetBase.h"
#include <EthernetUdp.h>

/**
* @class UserDatagramProtocol
* @brief ethernet UDP class.
*/
class UserDatagramProtocol  : public EthernetBase
{
public:
    UserDatagramProtocol();
    UserDatagramProtocol(BYTE* mac_address);
    UserDatagramProtocol(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6);
    virtual ~UserDatagramProtocol();

    virtual RESULT beginCommunication();
    virtual RESULT sendData(Message_if* data, WORD* send_address, SIZE_T address_size);
    virtual RESULT receiveData(Message_if* data){return FAIL;};
    virtual RESULT endCommunication();

    virtual WORD getReadPort();
    virtual void setReadPort(WORD port);

protected:
    virtual void initialize(void);
    EthernetUDP m_ethernet_udp;
    WORD m_read_port;

};
#endif // _USER_DATAGRAM_PROTOCOL_H_