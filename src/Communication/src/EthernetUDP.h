#ifndef _UDP_H_
#define _UDP_H_

#include "EthernetBase.h"

class IPAddress;

/**
* @class EthernetUdp
* @brief ethernet UDP class.
*/
class UserDatagramProtocol  : public TransportProtocol_if
{
public:
    EthernetUdp();
    EthernetUdp(BYTE* mac_address);
    EthernetUdp(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6);
    virtual ~EthernetUdp();

};
#endif // _UDP_H_