#include <Arduino.h>
#include <DHT.h>
#include "Dht11.h"

#define RETRY_TIME_DHT11    (2000)


Dht11::Dht11(pinno_t datapin_no) : DhtBase(datapin_no, DHT11)
{
    this->m_retry_timer.clearCount();
    this->m_retry_timer.startCount();
}

Dht11::~Dht11()
{
}

/**
* @brief start communication.
* @return result of the start.
* @retval SUCCESS   start communication.
* @retval FAIL      did not start.
*/
RESULT Dht11::start(void)
{
    if(this->m_retry_timer.isTimeUpMillis(RETRY_TIME_DHT11))
    {
        return DhtBase::start();
    }

    return FAIL;
}

/**
* @brief execute the read process.
* @param[in] option no used param.
* @param[in] option_count no used param.
*/
AnalogSensor_if::READ_STATUS Dht11::execute(WORD* option, WORD option_count)
{
    READ_STATUS result = NONE;
    if(this->m_retry_timer.isTimeUpMillis(RETRY_TIME_DHT11))
    {
        result = DhtBase::execute(option, option_count);
        this->m_retry_timer.clearCount();
        this->m_retry_timer.startCount();
    }

    return result;
}
