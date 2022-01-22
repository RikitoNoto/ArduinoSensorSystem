#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

#include "../src/UltraSonicSensor.h"
#include "spy/Arduino.h"
#include "spy/Timer.h"

TEST_GROUP(UltraSonicSensorTest)
{
    void setup()
    {
        Timer::setup();
        setupSpyArduino();
    }

    void teardown()
    {
    }
};

/**
* should be set pin mode echo to input.
*/
TEST(UltraSonicSensorTest, should_be_set_pin_mode_echo_to_input)
{
    UltraSonicSensor sensor(/*trig pin no*/8, /*echo pin no*/9);

    CHECK(checkPinCalled(9, INPUT));
}

/**
* should be set pin mode trig to output.
*/
TEST(UltraSonicSensorTest, should_be_set_pin_mode_trig_to_output)
{
    UltraSonicSensor sensor(/*trig pin no*/8, /*echo pin no*/9);

    CHECK(checkPinCalled(8, OUTPUT));
}

/**
* should be output trigger pin to high.
*/
TEST(UltraSonicSensorTest, should_be_output_trigger_pin_to_high)
{
    UltraSonicSensor sensor(/*trig pin no*/8, /*echo pin no*/9);
    UltraSonicSensor::DISTANCE_MM_T distance;
    sensor.read(&distance);
    CHECK(checkPinDigitalWrite(8, HIGH));
}

/**
* should be output trigger pin to low in 10 micro seconds.
*/
TEST(UltraSonicSensorTest, should_be_output_trigger_pin_to_low_in_10_micro_seconds)
{
    UltraSonicSensor sensor(/*trig pin no*/8, /*echo pin no*/9);
    UltraSonicSensor::DISTANCE_MM_T distance;
    sensor.read(&distance);
    Timer::setElapsedTimeMicros(10); // set 10us.

    CHECK(checkPinDigitalWrite(8, LOW));
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}