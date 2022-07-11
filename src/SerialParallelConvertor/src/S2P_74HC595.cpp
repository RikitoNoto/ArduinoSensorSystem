#include "S2P_74HC595.h"
#include <Arduino.h>
#include "ArduinoUtility.h"

#define SEND_DATA_BIT_COUNT     (8)

S2P_74HC595::S2P_74HC595(pinno_t serial, pinno_t clock, pinno_t clear)
{
    pinMode(serial, OUTPUT);
    pinMode(clock, OUTPUT);
    pinMode(clear, OUTPUT);

    this->m_clear_pin = clear;
    this->m_clock_pin = clock;
    this->m_serial_pin = serial;

    digitalWrite(this->m_clear_pin, HIGH);
    this->m_current_clock = LOW;
    this->m_status = IDLE;
    this->m_clock_count = 0;
}

/**
* @brief clear output.
* @details clear output time of 74HC595 require duration for 20ns,
*          so this function do not use timer.(frequency of arduino uno is 16MHz)
* @param[in] option no used param.
* @param[in] option_count no used param.
*/
void S2P_74HC595::clearOutput(void)
{
    digitalWrite(this->m_clear_pin, LOW);
    digitalWrite(this->m_clear_pin, HIGH);
}

BOOL S2P_74HC595::setSendData(BYTE data)
{
    this->m_send_data = data;
    return TRUE;
}

S2P_74HC595::SEND_STATUS S2P_74HC595::send(void)
{
    switch (this->m_status)
    {
        case IDLE:
            this->m_status = SENDING;
            // no break;
        case SENDING:
            // digitalWrite(this->m_serial_pin, LOW);
            digitalWrite(this->m_clock_pin, this->m_current_clock);
            if(this->m_current_clock == HIGH)
            {
                this->m_clock_count++;
            }
            else
            {
                SIGNAL data = ((this->m_send_data >> (SEND_DATA_BIT_COUNT - this->m_clock_count)) & 0x01) ? HIGH : LOW;
                digitalWrite(this->m_serial_pin, data);
            }

            // after sended clock 8 times,(a clock is one set of low and high.)
            // return the signal to low to complete.
            if( (this->m_clock_count >= SEND_DATA_BIT_COUNT) &&
                (this->m_current_clock == LOW) )
            {
                this->m_status = COMPLETE;
            }

            ArduinoUtility::notSignal(&this->m_current_clock);
            break;

        default:
            break;
    }

    return this->m_status;
}

void S2P_74HC595::clear(void)
{
    digitalWrite(this->m_serial_pin, LOW);
}
