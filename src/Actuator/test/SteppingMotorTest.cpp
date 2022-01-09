#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/SteppingMotor.h"
#include "spy/Arduino.h"

#define PIN_MODE_INDEX_COUNT    (32)
#define PIN_INFO_NONE           (0xFF)
#define PIN_WRITE_DO_NOT_CALL   (0xFF)

// pinMode
static uint8_t pin_mode_called_pin[PIN_MODE_INDEX_COUNT];
static uint8_t pin_mode_called_mode[PIN_MODE_INDEX_COUNT];

// digitalWrite
static uint8_t pin_write_called_pin[PIN_MODE_INDEX_COUNT];
static uint8_t pin_write_called_value[PIN_MODE_INDEX_COUNT];

void pinMode(uint8_t pin, uint8_t mode)
{
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // if called this pin or last of array.
        if( (pin_mode_called_pin[i] == pin) ||
            (pin_mode_called_pin[i] == PIN_INFO_NONE) )
        {
            pin_mode_called_pin[i]  = pin;
            pin_mode_called_mode[i] = mode;
            break;
        }
    }
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // if called this pin or last of array.
        if( (pin_write_called_pin[i] == pin) ||
            (pin_write_called_pin[i] == PIN_WRITE_DO_NOT_CALL) )
        {
            pin_write_called_pin[i]  = pin;
            pin_write_called_value[i] = val;
            break;
        }
    }
}

/**
 * @brief check called the function of pinMode with expected args.
 * @details if mode is PIN_INFO_NONE, do not check mode.
 */
bool checkPinCalled(uint8_t pin, uint8_t mode = PIN_INFO_NONE)
{
    // check all pins(pin_mode_called_pin, pin_mode_called_mode)
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // if pin called.
        if(pin_mode_called_pin[i] == pin)
        {
            // if set mode.
            if(mode != PIN_INFO_NONE)
            {
                // if mode is same.
                if(pin_mode_called_mode[i] == mode)
                {
                    return true;
                }
                // else is false.
            }
            // mode no set.
            else
            {
                // if pin is same, return true.
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief check called the function of digitalWrite with expected args.
 * @details if val is PIN_WRITE_DO_NOT_CALL, do not check val.
 */
bool checkPinDigitalWrite(uint8_t pin, uint8_t val = PIN_WRITE_DO_NOT_CALL)
{
    // check all pins(pin_write_called_pin, pin_write_called_value)
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // if pin called.
        if(pin_write_called_pin[i] == pin)
        {
            // if set mode.
            if(val != PIN_WRITE_DO_NOT_CALL)
            {
                // if mode is same.
                if(pin_write_called_value[i] == val)
                {
                    return true;
                }
                // else is false.
            }
            // mode no set.
            else
            {
                // if pin is same, return true.
                return true;
            }
        }
    }

    return false;
}

class SteppingMotorSpy : public SteppingMotor
{
public:

    SteppingMotorSpy(BYTE pinA, BYTE pinNA, BYTE pinB, BYTE pinNB) : SteppingMotor(pinA, pinNA, pinB, pinNB)
    {

    }

    void step(STEP_DIRECTION step_direction)
    {
        SteppingMotor::step(step_direction);
        SteppingMotorSpy::step_count++;
    }

    void step(void)
    {
        SteppingMotor::step();
    }

    void reversStep(void)
    {
        SteppingMotor::reversStep();
    }

    void setup(void)
    {
        SteppingMotorSpy::step_count = 0;
    }

    static int step_count;
};
int SteppingMotorSpy::step_count = 0;

TEST_GROUP(SteppingMotorTest)
{
    void setup()
    {
        for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
        {
            // reset all the infos of pin mode.
            pin_mode_called_pin[i] = PIN_INFO_NONE;
            pin_mode_called_mode[i] = PIN_INFO_NONE;

            // reset all the pin value of pin output.
            pin_write_called_pin[i] = PIN_WRITE_DO_NOT_CALL;
            pin_write_called_value[i] = PIN_WRITE_DO_NOT_CALL;
        }
    }

    void teardown()
    {
    }

    void checkOutputPin_step1(void)
    {
        CHECK(checkPinDigitalWrite(8, HIGH));
        CHECK(checkPinDigitalWrite(9, LOW));
        CHECK(checkPinDigitalWrite(10, LOW));
        CHECK(checkPinDigitalWrite(11, HIGH));
    }

    void checkOutputPin_step2(void)
    {
        CHECK(checkPinDigitalWrite(8, HIGH));
        CHECK(checkPinDigitalWrite(9, HIGH));
        CHECK(checkPinDigitalWrite(10, LOW));
        CHECK(checkPinDigitalWrite(11, LOW));
    }

    void checkOutputPin_step3(void)
    {
        CHECK(checkPinDigitalWrite(8, LOW));
        CHECK(checkPinDigitalWrite(9, HIGH));
        CHECK(checkPinDigitalWrite(10, HIGH));
        CHECK(checkPinDigitalWrite(11, LOW));
    }

    void checkOutputPin_step4(void)
    {
        CHECK(checkPinDigitalWrite(8, LOW));
        CHECK(checkPinDigitalWrite(9, LOW));
        CHECK(checkPinDigitalWrite(10, HIGH));
        CHECK(checkPinDigitalWrite(11, HIGH));
    }
};

/**
* should be create the instance.
*/
TEST(SteppingMotorTest, should_be_create_instance)
{
    SteppingMotor stepper;
}

/**
* should be set and get step angle.
*/
TEST(SteppingMotorTest, should_be_set_and_get_step_angle)
{
    SteppingMotor stepper;
    stepper.setStepAngle_mdeg(100);

    CHECK_EQUAL(100, stepper.getStepAngle_mdeg());
}

/**
* should be set pinmode.
*/
TEST(SteppingMotorTest, should_be_set_pinmode_two_phase)
{
    SteppingMotor stepper(8, 9, 10, 11);

    CHECK(checkPinCalled(8, OUTPUT));
    CHECK(checkPinCalled(9, OUTPUT));
    CHECK(checkPinCalled(10, OUTPUT));
    CHECK(checkPinCalled(11, OUTPUT));
}

/**
* should be rotate one step.
*/
TEST(SteppingMotorTest, should_be_rotate_one_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.step();

    checkOutputPin_step1();
}

/**
* should be rotate two step.
*/
TEST(SteppingMotorTest, should_be_rotate_two_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.step();
    stepper.step();

    checkOutputPin_step2();
}

/**
* should be rotate three step.
*/
TEST(SteppingMotorTest, should_be_rotate_three_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.step();
    stepper.step();
    stepper.step();

    checkOutputPin_step3();
}

/**
* should be rotate four step.
*/
TEST(SteppingMotorTest, should_be_rotate_four_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.step();
    stepper.step();
    stepper.step();
    stepper.step();

    checkOutputPin_step4();
}

/**
* should be rotate five step.
*/
TEST(SteppingMotorTest, should_be_rotate_five_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.step();
    stepper.step();
    stepper.step();
    stepper.step();
    stepper.step();

    checkOutputPin_step1();
}

/**
* should be rotate thirty step.
*/
TEST(SteppingMotorTest, should_be_rotate_thirty_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    for(int i=0; i<30; i++)
    {
        stepper.step();
    }

    checkOutputPin_step2();
}

/**
* should be rotate revers one step.
*/
TEST(SteppingMotorTest, should_be_rotate_revers_one_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);
    stepper.reversStep();

    checkOutputPin_step1();
}

/**
* should be rotate revers two step.
*/
TEST(SteppingMotorTest, should_be_rotate_revers_two_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);
    stepper.reversStep();
    stepper.reversStep();

    checkOutputPin_step4();
}

/**
* should be rotate revers three step.
*/
TEST(SteppingMotorTest, should_be_rotate_revers_three_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);
    stepper.reversStep();
    stepper.reversStep();
    stepper.reversStep();

    checkOutputPin_step3();
}

/**
* should be rotate revers forth step.
*/
TEST(SteppingMotorTest, should_be_rotate_revers_forth_step)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);
    stepper.reversStep();
    stepper.reversStep();
    stepper.reversStep();
    stepper.reversStep();

    checkOutputPin_step2();
}

/**
* should be rotate with angle.
*/
TEST(SteppingMotorTest, should_be_rotate_with_angle)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.setStepAngle_mdeg(10);
    stepper.moveWithAngle_mdeg(100);

    for(int i=1; i<11 ; i++)
    {
        stepper.run();
        switch (i%4)
        {
            case 1: // step 1
                checkOutputPin_step1();
                break;

            case 2: // step 2
                checkOutputPin_step2();
                break;

            case 3: // step 3
                checkOutputPin_step3();
                break;

            case 0: // step 4
                checkOutputPin_step4();
                break;

            default:
                // fail.
                CHECK(FALSE);
                break;
        }
    }

    stepper.run();

    // should be stop in step 2.
    //FIXME: why fail when call check method and comment out CHECK methods.
    //checkOutputPin_step2();
    CHECK(checkPinDigitalWrite(8, HIGH));
    CHECK(checkPinDigitalWrite(9, HIGH));
    CHECK(checkPinDigitalWrite(10, LOW));
    CHECK(checkPinDigitalWrite(11, LOW));

}

/**
* should be not rotate with 0 angle.
*/
TEST(SteppingMotorTest, should_be_not_rotate_with_0_angle)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.setStepAngle_mdeg(10);
    stepper.moveWithAngle_mdeg(0);

    stepper.run();
    CHECK(checkPinDigitalWrite(8, LOW));
    CHECK(checkPinDigitalWrite(9, LOW));
    CHECK(checkPinDigitalWrite(10, LOW));
    CHECK(checkPinDigitalWrite(11, LOW));
}

/**
* should be return status idle when be not running.
*/
TEST(SteppingMotorTest, should_be_return_status_idle_when_be_not_running)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.setStepAngle_mdeg(10);

    CHECK_EQUAL(SteppingMotor::EXECUTE_STATUS::IDLE, stepper.run());
}

/**
* should be return status execute when running.
*/
TEST(SteppingMotorTest, should_be_return_status_execute_when_running)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.setStepAngle_mdeg(10);
    stepper.moveWithAngle_mdeg(100);

    for(int i=1; i<11 ; i++)
    {
        CHECK_EQUAL(SteppingMotor::EXECUTE_STATUS::EXECUTING, stepper.run());
    }
}

/**
* should be return status complete when complete.
*/
TEST(SteppingMotorTest, should_be_return_status_complete_when_complete)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.setStepAngle_mdeg(10);
    stepper.moveWithAngle_mdeg(100);

    for(int i=1; i<11 ; i++)
    {
        stepper.run();
    }

    CHECK_EQUAL(SteppingMotor::EXECUTE_STATUS::COMPLETE, stepper.run());
}

/**
* should be return status idle when return complete.
*/
TEST(SteppingMotorTest, should_be_return_status_idle_when_return_complete)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.setStepAngle_mdeg(10);
    stepper.moveWithAngle_mdeg(100);

    for(int i=1; i<11 ; i++)
    {
        stepper.run();
    }

    stepper.run();
    CHECK_EQUAL(SteppingMotor::EXECUTE_STATUS::IDLE, stepper.run());
}

/**
* should be not running after complete.
*/
TEST(SteppingMotorTest, should_be_not_running_after_complete)
{
    SteppingMotorSpy stepper(8, 9, 10, 11);

    stepper.setStepAngle_mdeg(10);
    stepper.moveWithAngle_mdeg(100);

    for(int i=1; i<11 ; i++)
    {
        stepper.run();
    }

    stepper.run();
    stepper.moveWithAngle_mdeg(10);
    CHECK_EQUAL(SteppingMotor::EXECUTE_STATUS::EXECUTING, stepper.run());
    checkOutputPin_step3();
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}