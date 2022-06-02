#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/Dht11.h"
#include <Arduino.h>
#include <Timer.h>

TEST_GROUP(Dht11)
{
    void setup()
    {
        setupSpyArduino();
    }

    void teardown()
    {
    }

    void sendResponce(pinno_t pin, Dht11* dht, void (*f)(Dht11*))
    {
        setReadValue(pin, LOW);
        for(WORD i=0; i<80; i++)
        {
            Timer::elapseTimeMicros(1);
            f(dht);
        }
        setReadValue(pin, HIGH);
        for(WORD i=0; i<80; i++)
        {
            Timer::elapseTimeMicros(1);
            f(dht);
        }
    }

    void sendData1bit(pinno_t pin, BOOL data, Dht11* dht, void (*f)(Dht11*))
    {
        // low value for 50us as clock.
        for(WORD i=0; i<50; i++)
        {
            setReadValue(pin, LOW);
            Timer::elapseTimeMicros(1);
            f(dht);
        }

        WORD high_time = 0;
        if(data)
        {
            high_time = 70;
        }
        else
        {
            high_time = 28;
        }

        // high value for 50us as signal.
        for(WORD i=0; i<high_time; i++)
        {
            setReadValue(pin, HIGH);
            Timer::elapseTimeMicros(1);
            f(dht);
        }
    }

    void sendData(pinno_t pin, QWORD data, Dht11* dht, void (*f)(Dht11*))
    {
        for(WORD i=0; i<40 ; i++)
        {
            BOOL data = FALSE;
            if( ((data>>(40-i))&1) == 1)
            {
                data = TRUE;
            }

            sendData1bit(pin, data, dht, f);
        }
    }


    #define TIMER_UNIT_MS   1
    #define TIMER_UNIT_US   2

    void checkPinStateFor(BYTE pin, int mode, int out,  DWORD from_time, DWORD to_time, void (*f)(Dht11*) = nullptr, Dht11* dht = nullptr, int timer_unit = TIMER_UNIT_US)
    {
        for(DWORD i=0; i < (to_time - from_time) ; i++)
        {
            if(timer_unit == TIMER_UNIT_MS)
            {
                Timer::setElapsedTimeMillis(from_time + i);
            }
            else
            {
                Timer::setElapsedTimeMicros(from_time + i);
            }

            if(f != nullptr)
            {
                f(dht);
            }

            CHECK(checkPinCalled(pin, mode));
            if(mode == OUTPUT)
            {
                CHECK(checkPinDigitalWrite(pin, out));
            }
        }

    }

};

void execute(Dht11* dht)
{
    dht->execute();
}

/**
* should be DATA to LOW when start with pin 8.
*/
TEST(Dht11, should_be_DATA_to_LOW_when_start_with_pin_8)
{
    Dht11* dht = new Dht11(8);
    dht->start();
    checkPinStateFor(/*pin*/8, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/1, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    delete dht;
}

/**
* should be DATA to LOW when start with pin 10.
*/
TEST(Dht11, should_be_DATA_to_LOW_when_start_with_pin_10)
{
    Dht11* dht = new Dht11(10);
    dht->start();
    checkPinStateFor(/*pin*/10, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/1, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    delete dht;
}

/**
* should be DATA to LOW after 10ms from start with pin 8.
*/
TEST(Dht11, should_be_DATA_to_LOW_after_10ms_from_start_with_pin_8)
{
    Dht11* dht = new Dht11(8);
    dht->start();
    checkPinStateFor(/*pin*/8, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/10, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    delete dht;
}

/**
* should be DATA changes INPUT_PULLUP after 20ms from start with pin 8.
*/
TEST(Dht11, should_be_DATA_changes_INPUT_PULLUP_after_20ms_from_start_with_pin_8)
{
    Dht11* dht = new Dht11(8);
    dht->start();
    checkPinStateFor(/*pin*/8, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/20, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    // dht->execute();
    checkPinStateFor(/*pin*/8, /*mode*/INPUT_PULLUP, /*out*/0, /*from_time*/21, /*to_time*/21, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    delete dht;
}

/**
* should be DATA changes INPUT_PULLUP after 20ms from start with pin 10.
*/
TEST(Dht11, should_be_DATA_changes_INPUT_PULLUP_after_20ms_from_start_with_pin_10)
{
    Dht11* dht = new Dht11(10);
    dht->start();
    checkPinStateFor(/*pin*/10, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/20, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    // dht->execute();
    checkPinStateFor(/*pin*/10, /*mode*/INPUT_PULLUP, /*out*/0, /*from_time*/21, /*to_time*/21, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    delete dht;
}

/**
* should be read 0 as the value.
*/
TEST(Dht11, should_be_read_0_as_the_value)
{
    Dht11* dht = new Dht11(10);
    dht->start();
    checkPinStateFor(/*pin*/10, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/20, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    // dht->execute();
    checkPinStateFor(/*pin*/10, /*mode*/INPUT_PULLUP, /*out*/0, /*from_time*/21, /*to_time*/21, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);

    sendResponce(10, dht, execute);

    sendData(10, 0x0000000000, dht, execute);

    CHECK_EQUAL(0, dht->getData());
    delete dht;
}

// /**
// * should be read 1 as the value.
// */
// TEST(Dht11, should_be_read_1_as_the_value)
// {
//     Dht11* dht = new Dht11(10);
//     dht->start();
//     checkPinStateFor(/*pin*/10, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/20, /*f*/nullptr, /*unit*/TIMER_UNIT_MS);
//     dht->execute();
//     checkPinStateFor(/*pin*/10, /*mode*/INPUT_PULLUP, /*out*/0, /*from_time*/20, /*to_time*/21, /*f*/nullptr, /*unit*/TIMER_UNIT_MS);

//     sendResponce(10, dht, execute);

//     sendData(10, 0x0000010001, dht, execute);

//     CHECK_EQUAL(0x00010000, dht->getData());
//     delete dht;
// }

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}