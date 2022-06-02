#ifndef _TIMER_H_
#define _TIMER_H_

#include "DataType.h"

class Timer
{
public:
    // spy methods
    void startCount(void){};

    void clearCount(void){};

    void pauseCount(void){};

    BOOL isTimeUpMillis(DWORD check_time);
    BOOL isTimeUpMicros(DWORD check_time);

    DWORD getElapsedTimeMillis(void){return Timer::m_elapsed_time_millis;};
    DWORD getElapsedTimeMicros(void){return Timer::m_elapsed_time_micros;};

    // for test
    static void setup(void);
    static void setElapsedTimeMillis(DWORD elapsed_time);
    static void setElapsedTimeMicros(DWORD elapsed_time);

    static void elapseTimeMillis(DWORD elapse_time);
    static void elapseTimeMicros(DWORD elapse_time);
private:
    static DWORD m_elapsed_time_millis;
    static DWORD m_elapsed_time_micros;
};

#endif // _TIMER_H_