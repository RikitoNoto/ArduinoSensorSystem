#ifndef _ULTRA_SONIC_SENSOR_H_
#define _ULTRA_SONIC_SENSOR_H_

#include "DataType.h"
#include "DistanceSensor_if.h"

class UltraSonicSensor : public DistanceSensor_if
{
public:
    UltraSonicSensor(BYTE trig_pin_no, BYTE echo_pin_no);

    virtual READ_STATUS read(DISTANCE_MM_T* read_distance);
protected:
    void stateIdle(void);
    void stateOutputTrigger(void);
    BYTE m_trig_pin_no;
private:
    UltraSonicSensor();
};

#endif // _ULTRA_SONIC_SENSOR_H_