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
    this->m_current_step_index = 0;
    this->m_step_count = 0;
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
 * @brief move given to angles from current angle.
 * @param[in] mdeg degree to move.
 */
RESULT SteppingMotor::moveWithAngle_mdeg(ANGLE_DEG_T mdeg)
{
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
 * @param[in] step_direction direction of step. if direction is plus, inclement steps.
 */
void SteppingMotor::step(SteppingMotor::STEP_DIRECTION step_direction)
{
    if(this->m_step_function[this->m_current_step_index])
    {
        (this->*m_step_function[this->m_current_step_index])();

        switch(step_direction)
        {
            case STEP_DIRECTION::PLUS: // step move to 0->1..., step_count->0
                // if the last step count.
                if( (this->m_current_step_index+1) >= this->m_step_count)
                {
                    this->m_current_step_index = 0;
                }
                else
                {
                    this->m_current_step_index++;
                }
                break;

            case STEP_DIRECTION::MINUS: // step move to 2->1..., 0->step_count
                // if the first step count.
                if( this->m_current_step_index <= 0)
                {
                    this->m_current_step_index = this->m_step_count - 1;
                }
                else
                {
                    this->m_current_step_index--;
                }
                break;

            default:
                break;
        }
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