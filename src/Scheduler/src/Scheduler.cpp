#include "Scheduler.h"
#include <MsTimer2.h>

Scheduler* Scheduler::p_instance = nullptr;

#define ISR_INTERVAL    (1) // the interval of call ISR method.

#ifdef _DEBUG_
    #define _COUNT_FUNC_ACCESS_MODIFIER
#else
    #define _COUNT_FUNC_ACCESS_MODIFIER static
#endif
_COUNT_FUNC_ACCESS_MODIFIER void count1ms(void)
{
    Scheduler::getInstance()->ISR1ms();
}

Scheduler::Scheduler()
{
    for(WORD i=0; i<SCHEDULER_FUNC_MAX_COUNT ; i++)
    {
        this->m_schedule_infos[i].mp_schedule = nullptr;
        this->m_schedule_infos[i].m_count = 0;
        this->m_schedule_infos[i].m_is_started = FALSE;
    }
    this->is_timer_started = FALSE;
}

Scheduler::~Scheduler()
{

}

Scheduler* Scheduler::getInstance(void)
{
    if(Scheduler::p_instance == nullptr)
    {
        Scheduler::p_instance = new Scheduler();
    }

    return Scheduler::p_instance;
}

void Scheduler::deleteInstance(void)
{
    delete Scheduler::p_instance;
    Scheduler::p_instance = nullptr;
}

Scheduler::sid_t Scheduler::setSchedule(Schedule_if* schedule)
{
    for(Scheduler::sid_t id=0; id < SCHEDULER_FUNC_MAX_COUNT; id++)
    {
        if(this->m_schedule_infos[id].mp_schedule == nullptr)
        {
            this->m_schedule_infos[id].mp_schedule = schedule;
            return id;
        }
    }

    return SCHEDULER_INVALID_ID;
}

void Scheduler::start(Scheduler::sid_t id)
{
    this->m_schedule_infos[id].m_is_started = TRUE;

    // if did not start MsTimer2.
    if(this->is_timer_started == FALSE)
    {
        MsTimer2::set(ISR_INTERVAL, count1ms);  // set the count function.
        MsTimer2::start();                      // timer start.
    }
}

void Scheduler::ISR1ms()
{
    for(WORD i=0; i < SCHEDULER_FUNC_MAX_COUNT; i++)
    {
        if(this->m_schedule_infos[i].mp_schedule != nullptr)
        {
            // volatile members guaranteed load from memory(even if you don't need it),
            // so it load to local variable in advance.
            BOOL is_started = this->m_schedule_infos[i].m_is_started;
            count_t count = this->m_schedule_infos[i].m_count;

            // if started.
            if(is_started == TRUE)
            {
                count++;    // add 1ms to count.
                // if count is over set time.
                if(count >= this->m_schedule_infos[i].mp_schedule->getTime())
                {
                    this->m_schedule_infos[i].mp_schedule->execute();   // execute method.
                    count = 0;              // reset count.
                }
            }

            this->m_schedule_infos[i].m_count = count;
        }
    }

}