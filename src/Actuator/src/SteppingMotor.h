#ifndef _STEPPING_MOTOR_H_
#define _STEPPING_MOTOR_H_

#include "Arduino.h"
#include "Actuator_if.h"

class SteppingMotor : public Actuator_if
{
public:

    SteppingMotor();
    SteppingMotor(BYTE pinA, BYTE pinNA, BYTE pinB, BYTE pinNB);
    virtual ~SteppingMotor();

    virtual RESULT moveWithAngle_mdeg(ANGLE_DEG_T mdeg);

    void setStepAngle_mdeg(ANGLE_DEG_T angle_mdeg);
    ANGLE_DEG_T getStepAngle_mdeg(void);

    virtual void step(void);
    virtual void reversStep(void);

protected:

    enum PIN_OUTPUT: BYTE
    {
        OUTPUT_LOW = LOW,
        OUTPUT_HIGH = HIGH
    };

    enum STEP_DIRECTION : BYTE
    {
        PLUS = 0x01,
        MINUS = 0xFF
    };

    virtual void step(STEP_DIRECTION step_direction);

    virtual void outputPins(PIN_OUTPUT pin_A, PIN_OUTPUT pin_NA, PIN_OUTPUT pin_B, PIN_OUTPUT pin_NB);

    virtual void step1_TwoPhase(void);
    virtual void step2_TwoPhase(void);
    virtual void step3_TwoPhase(void);
    virtual void step4_TwoPhase(void);

    void (SteppingMotor::**m_step_function)(void);
    ANGLE_DEG_T m_step_angle_mdeg;
    BYTE m_pin_A;
    BYTE m_pin_NA;
    BYTE m_pin_B;
    BYTE m_pin_NB;
    BYTE m_step_count;
    BYTE m_current_step_index;
};

#endif // _STEPPING_MOTOR_H_