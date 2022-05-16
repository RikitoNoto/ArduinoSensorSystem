#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "DataType.h"

/**
* @class Schedule_if
* @brief interface of scheduler functions.
*/
class Schedule_if
{
public:
    virtual void execute(void) = 0;
    virtual DWORD getTime(void) = 0;
    enum SchduleType : BYTE
    {
        INTERVAL,       //  execute intarval for the time.
        AFTER_ONCE      //  execute once after the time.
    };
    virtual SchduleType getScheduleType(void) = 0;
};

/**
* @class Scheduler
* @brief class to schedule of functions.
*/
class Scheduler
{
public:
    static Scheduler* getInstance(void);
    static void deleteInstance(void);

    void setSchedule(Schedule_if* schedule);
private:
    Scheduler();
    virtual ~Scheduler();

    static Scheduler* instance;


    #ifdef _DEBUG_
        #define _COUNT_FUNC_ACCESS_MODIFIER public
    #else
        #define _COUNT_FUNC_ACCESS_MODIFIER private
    #endif
    _COUNT_FUNC_ACCESS_MODIFIER : void countTime(void);
};
#endif // _SCHEDULER_H_