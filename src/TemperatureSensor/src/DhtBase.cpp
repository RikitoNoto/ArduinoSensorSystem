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

RESULT DhtBase::start(void)
{
    this->m_dht->begin();
    return SUCCESS;
}

DhtBase::READ_STATUS DhtBase::execute(WORD* option, WORD option_count)
{
    this->m_temperature = static_cast<DWORD>(this->m_dht->readTemperature() * 1000);
    return READ_SUCCESS;
}


DWORD DhtBase::getData(void)
{
    return this->m_temperature;
}
