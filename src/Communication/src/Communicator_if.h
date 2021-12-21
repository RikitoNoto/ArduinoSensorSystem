#ifndef _COMMUNICATOR_IF_H_
#define _COMMUNICATOR_IF_H_

#include <DataType.h>
#include "Message_if.h"

class Communicator_if
{
public:
    virtual RESULT begin() = 0;
    virtual RESULT sendData(const Message_if* data, DWORD size) = 0;
    virtual RESULT receiveData(Message_if* data, DWORD* size) = 0;
};

#endif // _COMMUNICATOR_IF_H_