#include "Timer.h"

DWORD Timer::m_elapsed_time_millis = 0;
DWORD Timer::m_elapsed_time_micros = 0;

BOOL Timer::isTimeUpMillis(DWORD check_time)
{
    if(check_time >= Timer::m_elapsed_time_millis)
    {
        return TRUE;
    }
    return FALSE;
}

BOOL Timer::isTimeUpMicros(DWORD check_time)
{
    if(check_time >= Timer::m_elapsed_time_micros)
    {
        return TRUE;
    }
    return FALSE;
}

void Timer::setup(void)
{
    Timer::m_elapsed_time_millis = 0;
    Timer::m_elapsed_time_micros = 0;
}

void Timer::setElapsedTimeMillis(DWORD elapsed_time)
{
    Timer::m_elapsed_time_millis = elapsed_time;
}

void Timer::setElapsedTimeMicros(DWORD elapsed_time)
{
    Timer::m_elapsed_time_micros = elapsed_time;
}