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
    virtual void initilize(WORD* option=nullptr, WORD option_count=0){};
    virtual void start();

    virtual READ_STATUS execute(WORD* option=nullptr, WORD option_count=0);

    virtual DWORD getData(void);
    virtual DWORD getData(DWORD index){return 0;};
private:
    pinno_t m_data_pin_no;
    Timer m_timer;

    DWORD m_reading_index;
    BYTE* m_datas;

    enum PHASE : BYTE
    {
        NONE = 0,
        SEND_START_SIGNAL,
        RECEIVE_START_SIGNAL_LOW,
        RECEIVE_START_SIGNAL_HIGH,
        RECEIVE_DATAS,
        FINISH_COMPLETE,
        FINISH_FAILURE,
    };

    PHASE m_phase;
    PHASE m_pre_phase;

    PHASE sendStartSignalPhase(PHASE current, PHASE pre);
    PHASE receiveStartSignalLowPhase(PHASE current, PHASE pre);
    PHASE receiveStartSignalHighPhase(PHASE current, PHASE pre);
    PHASE receiveDatas(PHASE current, PHASE pre);
    RESULT sharpingDatas(void);

    DWORD constructData(BYTE* datas, DWORD size);

    RESULT checkParity(BYTE* datas);


    DWORD m_low_time;
    DWORD m_high_time;

    SIGNAL m_pre_signal;

    WORD m_temperature;
    WORD m_humidity;
};

#endif // _DHT_11_H_