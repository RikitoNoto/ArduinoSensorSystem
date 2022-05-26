#ifndef _SCHEDULE_IF_
#define _SCHEDULE_IF_

#include "DataType.h"

/**
* @class Schedule_if
* @brief interface of scheduler functions.
*/
class Schedule_if
{
public:
    virtual ~Schedule_if(){};
    virtual void execute(void) = 0;
    virtual DWORD getTime(void) = 0;
    enum SchduleType : BYTE
    {
        INTERVAL,       //  execute intarval for the time.
        AFTER_ONCE      //  execute once after the time.
    };
    virtual SchduleType getScheduleType(void) = 0;
};

#endif  // _SCHEDULE_IF_
