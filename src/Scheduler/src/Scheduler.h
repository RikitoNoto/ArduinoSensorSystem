#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "DataType.h"
#include "Schedule_if.h"

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
    void cancel(sid_t id);
    void clear(sid_t id);

    #define SCHEDULER_FUNC_MAX_COUNT    0x0F
    #define SCHEDULER_INVALID_ID        0xFF

    void ISR1ms(void);

private:
    Scheduler();
    virtual ~Scheduler();

    static Scheduler* p_instance;

    struct ScheduleInfo_s
    {
        volatile BOOL m_is_started;
        volatile count_t m_count;
        Schedule_if* mp_schedule;
    };
    ScheduleInfo_s m_schedule_infos[SCHEDULER_FUNC_MAX_COUNT];

    void clearScheduleInfo(ScheduleInfo_s* info);

    BOOL is_timer_started;
};
#endif // _SCHEDULER_H_
