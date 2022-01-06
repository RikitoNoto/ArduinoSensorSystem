#include "Timer.h"
#include <Arduino.h>

Timer::Timer()
{
    this->clearCount();
}

/**
 * @brief start count.
 * @details set time of both millis and micros when called this function.
 */
void Timer::startCount(void)
{
    // if did not pause.(initial)
    if(!this->m_is_paused)
    {
        this->m_is_started = TRUE;
        this->m_start_time_millis = millis();
        this->m_start_time_micros = micros();
    }
    // if restart after pausing.
    else
    {
        // set elapsed time + current time to start time.
        this->m_start_time_millis = millis() + this->getElapsedTimeMillis();
        this->m_start_time_micros = micros() + this->getElapsedTimeMicros();

        this->m_is_paused = FALSE;
    }
}

/**
 * @brief clear count.
 * @details clear all time held.
 */
void Timer::clearCount(void)
{
    this->m_is_started = FALSE;
    this->m_is_paused = FALSE;
    this->m_start_time_millis = 0;
    this->m_start_time_micros = 0;
}

/**
* @brief pause count.
*/
void Timer::pauseCount(void)
{
    this->m_is_paused = TRUE;
    this->m_pause_time_millis = millis();
    this->m_pause_time_micros = micros();
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
    if(this->getElapsedTimeMillis() >= check_time)
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
    if(this->getElapsedTimeMicros() >= check_time)
    {
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief return the time elapsed from called startCount.
 * @return elapsed time.
 * @note if did not call startCount method, return 0.
 *       when pause timer, return the time util pause from start.
 */
DWORD Timer::getElapsedTimeMillis()
{
    // did not start.
    if(!this->m_is_started)
    {
        return 0;
    }
    // when pause timer.
    else if(this->m_is_paused)
    {
        return this->m_pause_time_millis - this->m_start_time_millis;
    }
    // counting timer.
    else
    {
        return millis() - this->m_start_time_millis;
    }
}

/**
 * @brief return the time elapsed from called startCount.
 * @return elapsed time.
 * @note if did not call startCount method, return 0.
 *       when pause timer, return the time util pause from start.
 */
DWORD Timer::getElapsedTimeMicros()
{
    // did not start.
    if(!this->m_is_started)
    {
        return 0;
    }
    // when pause timer.
    else if(this->m_is_paused)
    {
        return this->m_pause_time_micros - this->m_start_time_micros;
    }
    // counting timer.
    else
    {
        return micros() - this->m_start_time_micros;
    }
}