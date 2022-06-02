#ifndef _DHT_11_H_
#define _DHT_11_H_

#include <DataType.h>
#include <AnalogSensor_if.h>
#include <Timer.h>

class Dht11 : public AnalogSensor_if
{
public:
    Dht11(pinno_t datapin_no);
    virtual ~Dht11();
    virtual void start();

    virtual READ_STATUS execute(WORD* option=nullptr, WORD option_count=0);

    virtual DWORD getData(void){return 0;};
private:
    pinno_t m_data_pin_no;
    Timer m_timer;

    enum PHASE : BYTE
    {
        SEND_START_SIGNAL = 1,
        RECEIVE_START_SIGNAL,
    };

    PHASE m_phase;
    PHASE m_pre_phase;

    PHASE sendStartSignalPhase(PHASE current, PHASE pre);
    PHASE receiveStartSignalPhase(PHASE current, PHASE pre);
};

#endif // _DHT_11_H_