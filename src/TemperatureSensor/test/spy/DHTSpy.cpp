#include "DHT.h"

DHT::DHT(uint8_t pin, uint8_t type, uint8_t count)
{
    this->m_pin = pin;
    this->m_type = type;
    this->is_called_begin = false;

    this->temperature = 0;
}


void DHT::begin(uint8_t usec)
{
    this->is_called_begin = true;
}


float DHT::readTemperature(bool S, bool force)
{
    return this->temperature;
}
