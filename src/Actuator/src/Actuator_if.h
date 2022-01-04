#ifndef _ACTUATOR_IF_H_
#define _ACTUATOR_IF_H_

#include "DataType.h"
#include "Point.h"

class Actuator_if
{
public:
    typedef SDWORD SPEED_T;
    typedef SDWORD POINT_T;
    typedef SDWORD ANGLE_DEG_T;
    typedef SDWORD ANGLE_RAD_T;

    enum EXECUTE_STATUS : BYTE
    {
        ERROR = FAIL,
        COMPLETE = SUCCESS,
        EXECUTING = SUCCESS+FAIL+1 // the literal is different of fail or complete.
    };

    // virtual RESULT moveWithSpeed(SPEED speed) = 0;
    // virtual RESULT moveWithPosition(Point<POINT>* to_position) = 0;
    // virtual RESULT moveWithPosition(POINT x, POINT y) = 0;
    virtual RESULT moveWithAngle_mdeg(ANGLE_DEG_T mdeg) = 0;
};

#endif // _ACTUATOR_IF_H_