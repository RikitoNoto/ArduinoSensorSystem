#include "Timer.h"
#include <Arduino.h>

Timer::Timer()
{
    this->stopCount();
}

/**
* @brief start count.
* @details set time of both millis and micros when called this function.
*/
void Timer::startCount(void)
{
    this->m_is_started = TRUE;
    this->m_start_time_millis = millis();
    this->m_start_time_micros = micros();
}

/**
* @brief stop count.
* @details clear all time held.
*/
void Timer::stopCount(void)
{
    this->m_is_started = FALSE;
    this->m_start_time_millis = 0;
    this->m_start_time_micros = 0;
}

/**
* @brief check time up millis.
* @param[in] check_time Time to check if it has passed.
* @return result.
* @retval TRUE elapsed.
* @retval FALSE not elapse.
*/
BOOL Timer::isTimeUpMillis(DWORD check_time)
{
    DWORD elapsed_time = millis() - this->m_start_time_millis;
    if(elapsed_time >= check_time)
    {
        return TRUE;
    }

    return FALSE;
}

/**
* @brief check time up micros.
* @param[in] check_time Time to check if it has passed.
* @return result.
* @retval TRUE elapsed.
* @retval FALSE not elapse.
*/
BOOL Timer::isTimeUpMicros(DWORD check_time)
{
    DWORD elapsed_time = micros() - this->m_start_time_micros;
    if(elapsed_time >= check_time)
    {
        return TRUE;
    }

    return FALSE;
}

/**
* @brief return the time elapsed from called startCount.
* @return elapsed time.
* @note if did not call startCount method, return 0.
*/
DWORD Timer::getElapsedTimeMillis()
{
    return this->m_is_started ? millis() - this->m_start_time_millis : 0;
}

/**
* @brief return the time elapsed from called startCount.
* @return elapsed time.
*/
DWORD Timer::getElapsedTimeMicros()
{
    return this->m_is_started ? micros() - this->m_start_time_micros : 0;
}