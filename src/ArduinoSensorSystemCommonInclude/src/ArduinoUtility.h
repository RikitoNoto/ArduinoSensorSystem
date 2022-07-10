#ifndef _ARDUINO_UTILITY_H_
#define _ARDUINO_UTILITY_H_

#include "DataType.h"

class ArduinoUtility
{
public:
    static inline SIGNAL notSignal(SIGNAL* signal)
    {
        *signal = !(*signal);
        return *signal;
    }

};

#endif // _ARDUINO_UTILITY_H_
