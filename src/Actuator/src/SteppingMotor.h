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

    virtual EXECUTE_STATUS run(void);

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
        NONE_SETTING = 0x00,
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
    ANGLE_DEG_T m_current_rotate_angle_mdeg;
    ANGLE_DEG_T m_target_rotate_angle_mdeg;
    ANGLE_DEG_T m_step_angle_mdeg;
    BYTE m_pin_A;
    BYTE m_pin_NA;
    BYTE m_pin_B;
    BYTE m_pin_NB;
    BYTE m_step_count;
    BYTE m_current_step;

    typedef EXECUTE_STATUS (SteppingMotor::*RunningFunction_t)(BOOL is_first);

    RunningFunction_t m_running_function;
    RunningFunction_t m_past_running_function;
    EXECUTE_STATUS runningFunctionIdle(BOOL is_first);
    EXECUTE_STATUS runningFunctionExecuting(BOOL is_first);
    // EXECUTE_STATUS runningFunctionComplete(BOOL is_first);
    // EXECUTE_STATUS runningFunctionError(BOOL is_first);

    virtual ANGLE_DEG_T incrementAngleDeg(ANGLE_DEG_T current_angle, ANGLE_DEG_T step_angle, STEP_DIRECTION rotate_direction);
    virtual BYTE proceedStep(BYTE current_step, BYTE step_count, STEP_DIRECTION rotate_direction);
};

#endif // _STEPPING_MOTOR_H_