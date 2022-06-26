#include "DhtBase.h"
#include <DHT.h>

DhtBase::DhtBase(pinno_t datapin_no, BYTE type)
{
    this->m_dht = new DHT(datapin_no, type);
}

DhtBase::~DhtBase()
{
    delete this->m_dht;
}

/**
* @brief start communication.
* @return result of the start.
* @retval SUCCESS   start communication.
* @retval FAIL      did not start.
*/
RESULT DhtBase::start(void)
{
    this->m_dht->begin();
    return SUCCESS;
}

/**
* @brief execute the read process.
* @param[in] option no used param.
* @param[in] option_count no used param.
*/
DhtBase::READ_STATUS DhtBase::execute(WORD* option, WORD option_count)
{
    this->m_temperature = static_cast<DWORD>(this->m_dht->readTemperature() * 1000);
    return READ_SUCCESS;
}

/**
* @brief get temperature.
* @return temperature
*/
DWORD DhtBase::getData(void)
{
    return this->m_temperature;
}
