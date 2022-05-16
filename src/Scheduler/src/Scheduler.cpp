#include "Scheduler.h"
#include <MsTimer2.h>

Scheduler* Scheduler::instance = nullptr;

Scheduler::Scheduler()
{

}

Scheduler::~Scheduler()
{

}

Scheduler* Scheduler::getInstance(void)
{
    if(Scheduler::instance == nullptr)
    {
        Scheduler::instance = new Scheduler();
    }

    return Scheduler::instance;
}

void Scheduler::deleteInstance(void)
{
    delete Scheduler::instance;
}

void Scheduler::setSchedule(Schedule_if* schedule)
{

}

void Scheduler::countTime()
{

}