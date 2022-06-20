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

#define HUM_DATA_BIT_SIZE   16
#define TEMP_DATA_BIT_SIZE  16

#define RECEIVE_DATA_TIME_UP_TIME   (100)

Dht11::Dht11(pinno_t datapin_no)
{
    this->m_data_pin_no = datapin_no;
    this->m_timer.clearCount();
    this->m_datas = new BYTE[_DHT_11_DATA_SIZE];
    memset(this->m_datas, 0, sizeof(BYTE)*(_DHT_11_DATA_SIZE));
    this->m_reading_index = 0;
    this->m_phase = NONE;

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
    READ_STATUS status = READ_STATUS::NONE;
    PHASE next = this->m_phase;

    switch (this->m_phase)
    {
    case PHASE::SEND_START_SIGNAL:
        next = this->sendStartSignalPhase(this->m_phase, this->m_pre_phase);
        status = READ_STATUS::READING;
        break;

    case PHASE::RECEIVE_START_SIGNAL_LOW:
        next = this->receiveStartSignalLowPhase(this->m_phase, this->m_pre_phase);
        status = READ_STATUS::READING;
        break;

    case PHASE::RECEIVE_START_SIGNAL_HIGH:
        next = this->receiveStartSignalHighPhase(this->m_phase, this->m_pre_phase);
        status = READ_STATUS::READING;
        break;

    case PHASE::RECEIVE_DATAS:
        next = this->receiveDatas(this->m_phase, this->m_pre_phase);
        status = READ_STATUS::READING;
        break;
    default:
        break;
    }

    this->m_pre_phase = this->m_phase;
    this->m_phase = next;

    if(this->m_phase == PHASE::FINISH_COMPLETE)
    {
        status = READ_STATUS::READ_SUCCESS;
    }
    else if(this->m_phase == PHASE::FINISH_FAILURE)
    {
        status = READ_STATUS::READ_FAILURE;
    }

    return status;
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
                if(this->sharpingDatas() == SUCCESS)
                {
                    next = PHASE::FINISH_COMPLETE;
                }
                else
                {
                    next = PHASE::FINISH_FAILURE;
                }
            }
        }
        this->m_timer.clearCount();
        this->m_timer.startCount(); // count start.

    }

    if(this->m_timer.getElapsedTimeMicros() >= RECEIVE_DATA_TIME_UP_TIME)
    {
        next = PHASE::FINISH_FAILURE;
    }

    this->m_pre_signal = read_data;
    return next;
}

RESULT Dht11::sharpingDatas()
{
    this->m_temperature = 0;
    this->m_humidity = 0;

    this->m_temperature = this->constructData(this->m_datas+HUM_DATA_BIT_SIZE, TEMP_DATA_BIT_SIZE);

    return this->checkParity(this->m_datas);
}

DWORD Dht11::constructData(BYTE* datas, DWORD size)
{
    DWORD data = 0;
    for(WORD i=0; i<size; i++)
    {
        data = data <<1;
        if(datas[i] == DATA_HIGH)
        {
            data |= 1;
        }
    }

    return data;
}

RESULT Dht11::checkParity(BYTE* datas)
{
    RESULT result = FAIL;
    BYTE parity = 0;
    BYTE data_sum = 0;
    for(WORD i=0; i<4; i++)
    {
        BYTE byte_data = 0;
        for(WORD j=0; j<8; j++)
        {
            byte_data = byte_data << 1;
            if(datas[i*8 + j] == DATA_HIGH)
            {
                byte_data |= 1;
            }
        }
        data_sum += byte_data;
    }

    for(WORD i=0; i<8; i++)
    {
        parity = parity << 1;
        if(datas[32 + i] == DATA_HIGH)
        {
            parity |= 1;
        }
    }

    if(data_sum == parity)
    {
        result = SUCCESS;
    }

    return result;
}

DWORD Dht11::getData(void)
{
    return this->m_temperature;
}