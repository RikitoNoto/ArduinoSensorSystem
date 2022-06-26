#ifndef _DHT_BASE_H_
#define _DHT_BASE_H_

#include "TemperatureSensor_if.h"
#include "Timer.h"

class DHT;

class DhtBase : public TemperatureSensor_if
{
public:
    DhtBase(pinno_t datapin_no, BYTE type);
    virtual ~DhtBase();
    virtual void initilize(WORD* option=nullptr, WORD option_count=0){};
    virtual RESULT start(void);
    virtual READ_STATUS execute(WORD* option=nullptr, WORD option_count=0);

    virtual DWORD getData(void);
    virtual DWORD getData(DWORD index){return 0;};

#ifndef TEST_SOURCE
protected:
#endif // TEST_SOURCE
    DHT* m_dht;
    DWORD m_temperature;
    Timer m_retry_timer;
};

#endif // _DHT_BASE_H_