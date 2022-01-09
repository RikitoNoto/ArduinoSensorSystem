#include "SteppingMotor.h"

#include <arduino.h>

// arduino not has 256 io pins.
#define  NO_SET_PIN     (0xFF)

SteppingMotor::SteppingMotor()
{
    this->m_step_angle_mdeg = 0;
    this->m_pin_A = NO_SET_PIN;
    this->m_pin_NA = NO_SET_PIN;
    this->m_pin_B = NO_SET_PIN;
    this->m_pin_NB = NO_SET_PIN;
    this->m_step_function = nullptr;
    this->m_current_step = 0;
    this->m_step_count = 0;
    this->m_target_rotate_angle_mdeg = 0;

    this->m_running_function = &SteppingMotor::runningFunctionIdle;
}

SteppingMotor::SteppingMotor(BYTE pinA, BYTE pinNA, BYTE pinB, BYTE pinNB) : SteppingMotor()
{
    // set mode of pins.
    this->m_pin_A = pinA;
    this->m_pin_NA = pinNA;
    this->m_pin_B = pinB;
    this->m_pin_NB = pinNB;

    pinMode(this->m_pin_A, OUTPUT);
    pinMode(this->m_pin_NA, OUTPUT);
    pinMode(this->m_pin_B, OUTPUT);
    pinMode(this->m_pin_NB, OUTPUT);

    // reset pins.
    this->outputPins(OUTPUT_LOW, OUTPUT_LOW, OUTPUT_LOW, OUTPUT_LOW);

    // set step setting.
    this->m_step_count = 4;

    // this->m_step_function = new (void (SteppingMotor::*[this->m_step_count])());
    this->m_step_function = new (void (SteppingMotor::*[this->m_step_count])());
    this->m_step_function[0] = &SteppingMotor::step1_TwoPhase;
    this->m_step_function[1] = &SteppingMotor::step2_TwoPhase;
    this->m_step_function[2] = &SteppingMotor::step3_TwoPhase;
    this->m_step_function[3] = &SteppingMotor::step4_TwoPhase;
}

SteppingMotor::~SteppingMotor()
{
    delete[] this->m_step_function;
}

/**
 * @brief should be execute at regular intervals.
 * @return current status of running.
 */
SteppingMotor::EXECUTE_STATUS SteppingMotor::run()
{
    BOOL is_first = FALSE;

    // bakc up current function for check first call.
    RunningFunction_t current_function = this->m_running_function;

    if(current_function != this->m_past_running_function)
    {
        is_first = TRUE;
    }

    // run function.
    EXECUTE_STATUS status = (this->*m_running_function)(is_first);

    this->m_past_running_function = current_function;

    return status;
}

/**
 * @brief move given to angles from current angle.
 * @param[in] mdeg degree to move.
 */
RESULT SteppingMotor::moveWithAngle_mdeg(ANGLE_DEG_T mdeg)
{
    this->m_target_rotate_angle_mdeg = mdeg;
    return FAIL;
}

/**
 * @brief set the step angle.
 * @details step angle is the angle when output one step.
 */
void SteppingMotor::setStepAngle_mdeg(SteppingMotor::ANGLE_DEG_T angle_mdeg)
{
    this->m_step_angle_mdeg = angle_mdeg;
}

/**
 * @brief get the address.
 * @details step angle is the angle when output one step.
 */
SteppingMotor::ANGLE_DEG_T SteppingMotor::getStepAngle_mdeg(void)
{
    return this->m_step_angle_mdeg;
}

/**
 * @brief output one step.
 * @param[in] rotate_direction direction of step. if direction is plus, inclement steps.
 */
void SteppingMotor::step(SteppingMotor::STEP_DIRECTION rotate_direction)
{
    if(this->m_step_function[this->m_current_step])
    {
        // execute step function.
        (this->*m_step_function[this->m_current_step])();

        // proceed step.
        this->m_current_step = this->proceedStep(this->m_current_step, this->m_step_count, rotate_direction);

        // increment current angle.
        this->m_current_rotate_angle_mdeg = this->incrementAngleDeg(this->m_current_rotate_angle_mdeg, this->m_step_angle_mdeg, rotate_direction);
    }
}

/**
 * @brief output one step.
 */
void SteppingMotor::step(void)
{
    this->step(STEP_DIRECTION::PLUS);
}

/**
 * @brief output one step.
 */
void SteppingMotor::reversStep(void)
{
    this->step(STEP_DIRECTION::MINUS);
}

/************************
 * two phase excitation.*
 ************************/
void SteppingMotor::step1_TwoPhase(void)
{
    this->outputPins(OUTPUT_HIGH, OUTPUT_LOW, OUTPUT_LOW, OUTPUT_HIGH);
}

void SteppingMotor::step2_TwoPhase(void)
{
    this->outputPins(OUTPUT_HIGH, OUTPUT_HIGH, OUTPUT_LOW, OUTPUT_LOW);
}

void SteppingMotor::step3_TwoPhase(void)
{
    this->outputPins(OUTPUT_LOW, OUTPUT_HIGH, OUTPUT_HIGH, OUTPUT_LOW);
}

void SteppingMotor::step4_TwoPhase(void)
{
    this->outputPins(OUTPUT_LOW, OUTPUT_LOW, OUTPUT_HIGH, OUTPUT_HIGH);
}

void SteppingMotor::outputPins(PIN_OUTPUT out_pin_A, PIN_OUTPUT out_pin_NA, PIN_OUTPUT out_pin_B, PIN_OUTPUT out_pin_NB)
{
    digitalWrite(this->m_pin_A, out_pin_A);
    digitalWrite(this->m_pin_NA, out_pin_NA);
    digitalWrite(this->m_pin_B, out_pin_B);
    digitalWrite(this->m_pin_NB, out_pin_NB);
}

/**
 * @brief should be execute at regular intervals.
 * @return current status of running.
 */
SteppingMotor::EXECUTE_STATUS SteppingMotor::runningFunctionIdle(BOOL is_first)
{
    if(this->m_target_rotate_angle_mdeg == 0)
    {
        return EXECUTE_STATUS::IDLE;
    }
    this->m_running_function = &SteppingMotor::runningFunctionExecuting;

    // execute running function.
    return (this->*m_running_function)(is_first);
}

/**
 * @brief should be execute at regular intervals.
 * @return current status of running.
 */
SteppingMotor::EXECUTE_STATUS SteppingMotor::runningFunctionExecuting(BOOL is_first)
{
    // set direction
    STEP_DIRECTION direction = STEP_DIRECTION::NONE_SETTING;
    if(this->m_target_rotate_angle_mdeg > 0)
    {
        direction = STEP_DIRECTION::PLUS;
    }
    else if(this->m_target_rotate_angle_mdeg < 0)
    {
        direction = STEP_DIRECTION::MINUS;
    }

    // is complete?
    if(this->m_current_rotate_angle_mdeg >= this->m_target_rotate_angle_mdeg)
    {
        // complete
        this->m_current_rotate_angle_mdeg = 0;
        this->m_target_rotate_angle_mdeg = 0;
        this->m_running_function = &SteppingMotor::runningFunctionIdle;
        return EXECUTE_STATUS::COMPLETE;
    }

    // running.
    this->step(direction);

    return EXECUTE_STATUS::EXECUTING;
}

// /**
//  * @brief should be execute at regular intervals.
//  * @return current status of running.
//  */
// SteppingMotor::EXECUTE_STATUS SteppingMotor::runningFunctionComplete(BOOL is_first)
// {

// }

// /**
//  * @brief should be execute at regular intervals.
//  * @return current status of running.
//  */
// SteppingMotor::EXECUTE_STATUS SteppingMotor::runningFunctionError(BOOL is_first)
// {

// }

/**
 * @brief  increment the step angle as degree.
 * @param[in] current_angle current angle.
 * @param[in] step_angle step angle.
 * @param[in] rotate_direction rotate direction.
 * @return incremented angle.
 */
SteppingMotor::ANGLE_DEG_T SteppingMotor::incrementAngleDeg(ANGLE_DEG_T current_angle, ANGLE_DEG_T step_angle, STEP_DIRECTION rotate_direction)
{
    // increment or decrement current angle.
    switch(rotate_direction)
    {
        case STEP_DIRECTION::PLUS:
            current_angle += step_angle;
            break;

        case STEP_DIRECTION::MINUS:
            current_angle -= step_angle;
            break;

        default:
            break;
    }

    return current_angle;
}

/**
 * @brief  proceed steps.
 * @param[in] current_step current step.
 * @param[in] step_count step count of this instance.
 * @param[in] rotate_direction rotate direction.
 * @return proceed steps.
 */
BYTE SteppingMotor::proceedStep(BYTE current_step, BYTE step_count, STEP_DIRECTION rotate_direction)
{
    switch(rotate_direction)
    {
        case STEP_DIRECTION::PLUS: // step move to 0->1..., step_count->0
            // if the last step count.
            if( (current_step + 1) >= step_count)
            {
                current_step = 0;
            }
            else
            {
                current_step++;
            }
            break;

        case STEP_DIRECTION::MINUS: // step move to 2->1..., 0->step_count
            // if the first step count.
            if( current_step <= 0)
            {
                current_step = step_count - 1;
            }
            else
            {
                current_step--;
            }
            break;

        default:
            break;
    }

    return current_step;
}