#include "Timer.h"

DWORD Timer::m_abs_elapsed_time_millis = 0;
DWORD Timer::m_abs_elapsed_time_micros = 0;


Timer::Timer()
{
    this->m_count_millis = 0;
    this->m_count_micros = 0;
}

void Timer::startCount(void)
{
    this->m_count_millis = Timer::m_abs_elapsed_time_millis;
    this->m_count_micros = Timer::m_abs_elapsed_time_micros;
};

void Timer::clearCount(void)
{
    this->m_count_millis = 0;
    this->m_count_micros = 0;
};

BOOL Timer::isTimeUpMillis(DWORD check_time)
{
    if(check_time <= this->getElapsedTimeMillis())
    {
        return TRUE;
    }
    return FALSE;
}

BOOL Timer::isTimeUpMicros(DWORD check_time)
{
    if(check_time <= this->getElapsedTimeMicros())
    {
        return TRUE;
    }
    return FALSE;
}

DWORD Timer::getElapsedTimeMillis(void)
{
    return Timer::m_abs_elapsed_time_millis - this->m_count_millis;
}

DWORD Timer::getElapsedTimeMicros(void)
{
    return Timer::m_abs_elapsed_time_micros - this->m_count_micros;
}

void Timer::setup(void)
{
    Timer::m_abs_elapsed_time_millis = 0;
    Timer::m_abs_elapsed_time_micros = 0;
}

void Timer::setElapsedTimeMillis(DWORD elapsed_time)
{
    Timer::m_abs_elapsed_time_millis = elapsed_time;
    Timer::m_abs_elapsed_time_micros = elapsed_time*1000;
}

void Timer::setElapsedTimeMicros(DWORD elapsed_time)
{
    Timer::m_abs_elapsed_time_micros = elapsed_time;
}

void Timer::elapseTimeMillis(DWORD elapse_time)
{
    Timer::m_abs_elapsed_time_millis += elapse_time;
    Timer::m_abs_elapsed_time_micros += elapse_time*1000;
}

void Timer::elapseTimeMicros(DWORD elapse_time)
{
    Timer::m_abs_elapsed_time_micros += elapse_time;
}