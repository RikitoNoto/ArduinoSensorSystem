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
    typedef QWORD count_t;
    typedef WORD sid_t;
    static Scheduler* getInstance(void);
    static void deleteInstance(void);

    sid_t setSchedule(Schedule_if* schedule);

    void start(sid_t id);

    #define SCHEDULER_FUNC_MAX_COUNT    0x0F
    #define SCHEDULER_INVALID_ID        0xFF

    void ISR1ms(void);

private:
    Scheduler();
    virtual ~Scheduler();

    static Scheduler* p_instance;

    struct ScheduleInfo_s
    {
        BOOL m_is_started;
        count_t m_count;
        Schedule_if* mp_schedule;
    };
    ScheduleInfo_s m_schedule_infos[SCHEDULER_FUNC_MAX_COUNT];

    BOOL is_timer_started;
};
#endif // _SCHEDULER_H_