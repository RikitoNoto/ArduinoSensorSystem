#include <Arduino.h>
#include "Dht11.h"
#include "Timer.h"

Dht11::Dht11(pinno_t datapin_no)
{
    this->m_data_pin_no = datapin_no;
    this->m_timer.clearCount();
}

Dht11::~Dht11()
{

}

void Dht11::start()
{
    pinMode(this->m_data_pin_no, OUTPUT);
    digitalWrite(this->m_data_pin_no, LOW);

    this->m_timer.startCount();
    this->m_phase = PHASE::SEND_START_SIGNAL;
}

Dht11::READ_STATUS Dht11::execute(WORD* option, WORD option_count)
{
    PHASE next = this->m_phase;

    switch (this->m_phase)
    {
    case PHASE::SEND_START_SIGNAL:
        next = this->sendStartSignalPhase(this->m_phase, this->m_pre_phase);
        break;

    case PHASE::RECEIVE_START_SIGNAL:
        next = this->receiveStartSignalPhase(this->m_phase, this->m_pre_phase);
        break;

    default:
        break;
    }

    this->m_pre_phase = this->m_phase;
    this->m_phase = next;

    return READ_STATUS::NONE;
}

Dht11::PHASE Dht11::sendStartSignalPhase(PHASE current, PHASE pre)
{
    PHASE next = current;

    pinMode(this->m_data_pin_no, OUTPUT);
    digitalWrite(this->m_data_pin_no, LOW);

    if(this->m_timer.isTimeUpMillis(20))
    {
        next = PHASE::RECEIVE_START_SIGNAL;
    }

    return next;
}

Dht11::PHASE Dht11::receiveStartSignalPhase(PHASE current, PHASE pre)
{
    if(current != pre)
    {
        this->m_timer.clearCount();
        this->m_timer.startCount();
    }
    pinMode(this->m_data_pin_no, INPUT_PULLUP);

    return current;
}
