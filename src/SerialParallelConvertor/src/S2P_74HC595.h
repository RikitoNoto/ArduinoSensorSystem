#ifndef _S2P_74HC595_H_
#define _S2P_74HC595_H_

#include "DataType.h"
#include "SerialToParallelConvertor_if.h"

class S2P_74HC595 : public SerialToParallelConvertor_if
{
public:
    S2P_74HC595(pinno_t serial, pinno_t clock, pinno_t clear);
    S2P_74HC595(pinno_t serial, pinno_t clock, pinno_t clear, pinno_t rclock);

    SEND_STATUS send(void);
    void clear(void);

    void clearOutput(void);
    BOOL setSendData(BYTE data);

private:
    pinno_t m_clear_pin;
    pinno_t m_clock_pin;
    pinno_t m_serial_pin;
    pinno_t m_rclock_pin;

    SIGNAL m_current_clock;
    BYTE m_clock_count;

    BYTE m_send_data;

    SEND_STATUS m_status;

    SIGNAL getSerialDataBit(BYTE data, BYTE clock);
};

#endif // _S2P_74HC595_H_
