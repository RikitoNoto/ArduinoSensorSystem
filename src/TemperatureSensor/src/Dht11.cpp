#include <Arduino.h>
#include "Dht11.h"
#include "Timer.h"
#include <string.h>

#define START_SIGNAL_TIME_MS        (20)
#define START_RESPONCE_LOW_TIME_US  (80)
#define START_RESPONCE_HIGH_TIME_US (80)

#define _DHT_11_DATA_SIZE   (40)
#define DATA_HIGH       0x01
#define DATA_LOW        0x00
#define DATA_INVALID    0xFF

Dht11::Dht11(pinno_t datapin_no)
{
    this->m_data_pin_no = datapin_no;
    this->m_timer.clearCount();
    this->m_datas = new BYTE[_DHT_11_DATA_SIZE];
    memset(this->m_datas, 0, sizeof(BYTE)*(_DHT_11_DATA_SIZE));
    this->m_reading_index = 0;

    this->m_temperature = 0;
    this->m_humidity = 0;
}

Dht11::~Dht11()
{
    delete[] this->m_datas;
}

void Dht11::start()
{

    this->m_low_time = 0;
    this->m_high_time = 0;

    this->m_pre_signal = HIGH;

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

    case PHASE::RECEIVE_START_SIGNAL_LOW:
        next = this->receiveStartSignalLowPhase(this->m_phase, this->m_pre_phase);
        break;

    case PHASE::RECEIVE_START_SIGNAL_HIGH:
        next = this->receiveStartSignalHighPhase(this->m_phase, this->m_pre_phase);
        break;

    case PHASE::RECEIVE_DATAS:
        next = this->receiveDatas(this->m_phase, this->m_pre_phase);
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

    if(this->m_timer.isTimeUpMillis(START_SIGNAL_TIME_MS))
    {
        next = PHASE::RECEIVE_START_SIGNAL_LOW;
    }

    return next;
}

Dht11::PHASE Dht11::receiveStartSignalLowPhase(PHASE current, PHASE pre)
{
    PHASE next = current;

    if(current != pre)
    {
        pinMode(this->m_data_pin_no, INPUT_PULLUP);
    }

    if(digitalRead(this->m_data_pin_no) != LOW)
    {
        this->m_timer.clearCount();
        this->m_timer.startCount();
    }

    if(this->m_timer.isTimeUpMicros(START_RESPONCE_LOW_TIME_US))
    {
        next = PHASE::RECEIVE_START_SIGNAL_HIGH;
    }

    return next;
}

Dht11::PHASE Dht11::receiveStartSignalHighPhase(PHASE current, PHASE pre)
{
    PHASE next = current;

    if(current != pre)
    {
        pinMode(this->m_data_pin_no, INPUT_PULLUP);
    }

    if(digitalRead(this->m_data_pin_no) != HIGH)
    {
        this->m_timer.clearCount();
        this->m_timer.startCount();
    }

    if(this->m_timer.isTimeUpMicros(START_RESPONCE_HIGH_TIME_US))
    {
        next = PHASE::RECEIVE_DATAS;
    }

    return next;
}

Dht11::PHASE Dht11::receiveDatas(PHASE current, PHASE pre)
{
    PHASE next = current;
    SIGNAL read_data = digitalRead(this->m_data_pin_no);
    if(current != pre)
    {
        memset(this->m_datas, 0, sizeof(BYTE)*(_DHT_11_DATA_SIZE));
        this->m_timer.clearCount();
        this->m_timer.startCount();
    }


    // if change signal
    if(read_data != this->m_pre_signal)
    {
        if(this->m_pre_signal == LOW)
        {
            this->m_low_time = this->m_timer.getElapsedTimeMicros();
        }
        else if((this->m_pre_signal == HIGH) && (this->m_low_time >= 50))
        {
            DWORD elapsed_time = this->m_timer.getElapsedTimeMicros();
            BYTE data = DATA_INVALID;

            // the signal is low when the time elapsed 26-28ms.
            if( (elapsed_time >= 26) && (elapsed_time <= 28) )
            {
                data = DATA_HIGH;
            }
            // the signal is high when the time elapsed 50-70ms.
            else if( (elapsed_time >= 50) && (elapsed_time <= 70) )
            {
                data = DATA_LOW;
            }

            this->m_datas[this->m_reading_index] = data;
            this->m_reading_index++;
            if(this->m_reading_index == _DHT_11_DATA_SIZE)
            {
                this->sharpingDatas();
            }
        }
        this->m_timer.clearCount();
        this->m_timer.startCount(); // count start.

    }

    this->m_pre_signal = read_data;
    return next;
}

RESULT Dht11::sharpingDatas()
{
    this->m_temperature = 0;
    this->m_humidity = 0;

    #define HUM_DATA_BIT_SIZE   16
    #define TEMP_DATA_BIT_SIZE  16


    for(WORD i=0; i<HUM_DATA_BIT_SIZE; i++)
    {
        this->m_humidity = this->m_humidity <<1;
        if(this->m_datas[i] == DATA_HIGH)
        {
            this->m_humidity |= 1;
        }
    }

    for(WORD i=0; i<TEMP_DATA_BIT_SIZE; i++)
    {
        this->m_temperature = this->m_temperature <<1;
        if(this->m_datas[i + HUM_DATA_BIT_SIZE] == DATA_HIGH)
        {
            this->m_temperature |= 1;
        }
    }

    return SUCCESS;
}

DWORD Dht11::getData(void)
{
    return this->m_temperature;
}