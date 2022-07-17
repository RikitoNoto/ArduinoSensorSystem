#ifndef _SERIAL_TO_PARALLEL_CONVERTOR_IF_H
#define _SERIAL_TO_PARALLEL_CONVERTOR_IF_H

#include "DataType.h"

class SerialToParallelConvertor_if
{
public:
    virtual BOOL setSendData(BYTE data) = 0;

    enum SEND_STATUS
    {
        IDLE,
        SENDING,
        COMPLETE,
    };

};
#endif // _SERIAL_TO_PARALLEL_CONVERTOR_IF_H