#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/Dht11.h"
#include <Arduino.h>
#include <Timer.h>

void execute(Dht11* dht);

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
            high_time = 28;
        }
        else
        {
            high_time = 70;
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
            BOOL bit_data = FALSE;
            if( ((data>>(39-i))&1) == 1)
            {
                bit_data = TRUE;
            }

            sendData1bit(pin, bit_data, dht, f);
        }
        setReadValue(pin, LOW);
        f(dht);
    }


    #define TIMER_UNIT_MS   1
    #define TIMER_UNIT_US   2

    void checkPinStateFor(BYTE pin, int mode, int out,  DWORD from_time, DWORD to_time, void (*f)(Dht11*) = nullptr, Dht11* dht = nullptr, int timer_unit = TIMER_UNIT_US, BOOL need_check=TRUE)
    {
        for(DWORD i=0; i <= (to_time - from_time) ; i++)
        {
            // set elapased time. first time is same of the from time.
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

            if(need_check)
            {
                CHECK(checkPinCalled(pin, mode));
            }

            if( (mode == OUTPUT) && (need_check) )
            {
                CHECK(checkPinDigitalWrite(pin, out));
            }
        }

    }

    void checkSendData(BYTE pin, DWORD data, DWORD expect, Dht11* dht=nullptr)
    {
        BOOL need_delete = FALSE;
        if(dht == nullptr)
        {
            dht = new Dht11(pin);
            need_delete = TRUE;
        }
        dht->start();
        checkPinStateFor(/*pin*/pin, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/20, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);

        sendResponce(pin, dht, execute);

        sendData(pin, data, dht, execute);

        CHECK_EQUAL(expect, dht->getData());
        if(need_delete)
        {
            delete dht;
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
    checkPinStateFor(/*pin*/10, /*mode*/INPUT_PULLUP, /*out*/0, /*from_time*/21, /*to_time*/21, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    delete dht;
}

/**
* should be read 0 as the value.
*/
TEST(Dht11, should_be_read_0_as_the_value)
{
    checkSendData(10, 0x0000000000, 0);
}

/**
* should be read 1 as the value.
*/
TEST(Dht11, should_be_read_1_as_the_value)
{
    checkSendData(10, 0x0000000101, 1);
}

/**
* should be read datas twice.
*/
TEST(Dht11, should_be_read_datas_twice)
{
    checkSendData(10, 0x0000000101, 1);
    checkSendData(10, 0x0000000202, 2);
}

/**
* should be return the complete when finish the communication to dht11.
*/
TEST(Dht11, should_be_return_the_complete_when_finish)
{
    Dht11* dht = new Dht11(10);
    checkSendData(10, 0x0000000101, 1, dht);
    CHECK_EQUAL(Dht11::READ_STATUS::READ_SUCCESS, dht->execute());
    delete dht;
}

/**
* should be return the reading for reading.
*/
TEST(Dht11, should_be_return_the_reading_for_reading)
{
    Dht11* dht = new Dht11(10);
    dht->start();
    CHECK_EQUAL(Dht11::READ_STATUS::READING, dht->execute());
    delete dht;
}

/**
* should be return the failure when received invalid parity.
*/
TEST(Dht11, should_be_return_the_failure_when_received_invalid_parity)
{
    Dht11* dht = new Dht11(10);
    checkSendData(/*pin*/10, /*data*/0x0000000100, /*expect*/1, dht);
    CHECK_EQUAL(Dht11::READ_STATUS::READ_FAILURE, dht->execute());
    delete dht;
}

/**
* should be not do anything when not started.
*/
TEST(Dht11, should_be_not_do_anything_when_not_started)
{
    Dht11* dht = new Dht11(10);
    checkPinStateFor(/*pin*/10, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/20, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS, FALSE);
    sendResponce(10, dht, execute);
    sendData(10, 0x0000000101, dht, execute);

    CHECK_FALSE(checkPinCalled(10)); // shoud not called
    delete dht;
}

/**
* should be return failure when receive time out.
*/
TEST(Dht11, should_be_return_failure_when_receive_time_out)
{
    Dht11* dht = new Dht11(10);
    dht->start();
    checkPinStateFor(/*pin*/10, /*mode*/OUTPUT, /*out*/LOW, /*from_time*/0, /*to_time*/20, /*f*/execute, /*dht*/dht, /*unit*/TIMER_UNIT_MS);
    sendResponce(10, dht, execute);

    // elapse 100us.
    for(WORD i=0; i<101; i++)
    {
        setReadValue(10, LOW);
        Timer::elapseTimeMicros(1);
        dht->execute();
    }
    CHECK_EQUAL(Dht11::READ_STATUS::READ_FAILURE, dht->execute());

    delete dht;
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}