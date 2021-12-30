#ifndef _MESSAGE_IF_H_
#define _MESSAGE_IF_H_

#include <DataType.h>
#include <stdint.h>
#include <stddef.h>

class Message_if
{
public:
    virtual uint8_t* getData_uint8(void) = 0;
    virtual size_t getDataSize_sizet_uint8(void) = 0;
};

#endif // _MESSAGE_IF_H_