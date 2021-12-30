#ifndef _COMMUNICATOR_IF_H_
#define _COMMUNICATOR_IF_H_

#include <DataType.h>
#include "Message_if.h"

class Communicator_if
{
public:
    virtual RESULT beginCommunication() = 0;
    virtual RESULT sendData(Message_if* data, WORD* send_address, SIZE_T address_size) = 0;
    virtual RESULT receiveData(Message_if* data) = 0;
    virtual RESULT endCommunication() = 0;
};

#endif // _COMMUNICATOR_IF_H_