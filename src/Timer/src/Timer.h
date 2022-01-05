#ifndef _TIMER_H_
#define _TIMER_H_

#include <DataType.h>

class Timer
{
public:
    Timer();
    void startCount(void);
    void stopCount(void);

    BOOL isTimeUpMillis(DWORD check_time);
    BOOL isTimeUpMicros(DWORD check_time);

    DWORD getElapsedTimeMillis(void);
    DWORD getElapsedTimeMicros(void);

private:
    BOOL m_is_started;
    DWORD m_start_time_millis;
    DWORD m_start_time_micros;
};

#endif // _TIMER_H_