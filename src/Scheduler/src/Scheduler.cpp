#include "Scheduler.h"
#include <MsTimer2.h>

Scheduler* Scheduler::p_instance = nullptr;

Scheduler::Scheduler()
{
    for(WORD i=0; i<SCHEDULER_FUNC_MAX_COUNT ; i++)
    {
        this->m_schedule_infos[i].mp_schedule = nullptr;
        this->m_schedule_infos[i].m_count = 0;
        this->m_schedule_infos[i].m_is_started = FALSE;
    }
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
}

void Scheduler::count1ms()
{
    for(WORD i=0; i < SCHEDULER_FUNC_MAX_COUNT; i++)
    {
        if(this->m_schedule_infos[i].mp_schedule != nullptr)
        {
            // if started.
            if(this->m_schedule_infos[i].m_is_started == TRUE)
            {
                this->m_schedule_infos[i].m_count++;    // add 1ms to count.
                // if count is over set time.
                if(this->m_schedule_infos[i].m_count >= this->m_schedule_infos[i].mp_schedule->getTime())
                {
                    this->m_schedule_infos[i].mp_schedule->execute();   // execute method.
                    this->m_schedule_infos[i].m_count = 0;              // reset count.
                }
            }
        }
    }

}