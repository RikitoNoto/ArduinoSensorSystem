#ifndef _DISTANCE_SENSOR_IF_H_
#define _DISTANCE_SENSOR_IF_H_

class DistanceSensor_if
{
public:
    typedef DWORD DISTANCE_MM_T;

    enum READ_STATUS : BYTE
    {
        READING = 0x00,
        COMPLETE = 0x01
    };

    virtual READ_STATUS read(DISTANCE_MM_T* read_distance) = 0;

};

#endif // _DISTANCE_SENSOR_IF_H_