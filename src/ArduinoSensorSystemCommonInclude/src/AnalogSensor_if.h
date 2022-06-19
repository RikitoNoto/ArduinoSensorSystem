#ifndef _ANALOG_SENSOR_H_
#define _ANALOG_SENSOR_H_

#include "DataType.h"

class AnalogSensor_if
{
public:
    virtual ~AnalogSensor_if(){};

    enum READ_STATUS : BYTE
    {
        NONE = 0,
        READING,
        READ_SUCCESS,
        READ_FAILURE,
    };

    virtual void start(void) = 0;
    virtual READ_STATUS execute(WORD* option=nullptr, WORD option_count=0) = 0;

    virtual DWORD getData(void) = 0;
};

#endif  //_ANALOG_SENSOR_H_