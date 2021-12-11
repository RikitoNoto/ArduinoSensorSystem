#ifndef _ETHERNET_SHIELD_H_
#define _ETHERNET_SHIELD_H_

#include "Communicator_if.h"

class EthernetShieldUdp : public Communicator_if
{
public:
    EthernetShieldUdp(char* macAddress);
    virtual ~EthernetShieldUdp(){};
    virtual RESULT sendData(const Message_if* data, DWORD size){return FAIL;};
    virtual RESULT receiveData(Message_if* data, DWORD* size){return FAIL;};
};

#endif // _ETHERNET_SHIELD_H_