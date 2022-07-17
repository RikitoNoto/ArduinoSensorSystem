#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <Arduino.h>
#include "string.h"
#include "S2P_74HC595.h"

#define _PIN_COUNT_     (8)

static int pre_signal = LOW;
static int signal_counter = 0;
static int expect_signals[_PIN_COUNT_] = {LOW};

TEST_GROUP(S2P_74HC595Test)
{
    static const BYTE PARALLEL_OUTPUT_COUNT = 8;
    void setup()
    {
        setupSpyArduino();
        pre_signal = LOW;
        memset(expect_signals, LOW, sizeof(expect_signals));
        signal_counter = 0;
    }

    void teardown()
    {
        tearDownArduino();
    }

    void checkClock(S2P_74HC595* s2p, uint8_t pin)
    {
        for(int i=0; i<PARALLEL_OUTPUT_COUNT+1; i++)
        {
            CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p->send());
            CHECK(isPinOutput(pin, LOW));

            CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p->send());
            CHECK(isPinOutput(pin, HIGH));
        }
    }

};

bool checkOutput(uint8_t pin, uint8_t val)
{
    if(pin == 3){
        if( (val == LOW) && (pre_signal == HIGH)){
            CHECK(isPinOutput(4, expect_signals[signal_counter]));
            signal_counter++;
        }
        pre_signal = val;
        if(signal_counter == 8){
            return false;
        }
    }
    return true;
}

/**
* should be create a instance.
*/
TEST(S2P_74HC595Test, should_be_create_a_instance)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
}

/**
* should be set the pins as output.
*/
TEST(S2P_74HC595Test, should_be_set_the_pins_as_output1)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);

    CHECK(isPinMode(3, OUTPUT));
    CHECK(isPinMode(4, OUTPUT));
    CHECK(isPinMode(5, OUTPUT));
}

/**
* should be set the pins as output.
*/
TEST(S2P_74HC595Test, should_be_set_the_pins_as_output2)
{
    S2P_74HC595 s2p(/*SER*/ 6, /*SRCLK*/ 7, /*SRCLR*/ 8);

    CHECK(isPinMode(6, OUTPUT));
    CHECK(isPinMode(7, OUTPUT));
    CHECK(isPinMode(8, OUTPUT));
}

/**
* should be output clear pin when clear output.
*/
TEST(S2P_74HC595Test, should_be_output_clear_pin_when_clear_output)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.clearOutput();
    CHECK(isWriteLow(5));
}

/**
* should be not output clear pin after clear output.
*/
TEST(S2P_74HC595Test, should_be_not_output_clear_pin_after_clear_output)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.clearOutput();
    CHECK(isWriteLow(5));
    CHECK(isPinOutput(5, HIGH));
}

/**
* should be not output clear pin when it is not clear output.
*/
TEST(S2P_74HC595Test, should_be_not_output_clear_pin_when_not_clear_output)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    CHECK(isPinOutput(5, HIGH));
}

/**
* should be set send data.
*/
TEST(S2P_74HC595Test, should_be_set_send_data)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    CHECK_EQUAL(TRUE, s2p.setSendData(0));
}

/**
* should be set low into serial pin when clear.
*/
TEST(S2P_74HC595Test, should_be_set_low_into_serial_pin_when_clear)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(0);
    s2p.clear();
    CHECK(isPinOutput(4, LOW));
}

/**
* should be not able to set data for sending.
*/
TEST(S2P_74HC595Test, should_be_not_able_to_set_data_for_sending)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    CHECK_EQUAL(TRUE, s2p.setSendData(0));
    for(int i=0; i<PARALLEL_OUTPUT_COUNT+1; i++)
    {
        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK_EQUAL(FALSE, s2p.setSendData(0));
        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK_EQUAL(FALSE, s2p.setSendData(0));
    }
    CHECK_EQUAL(S2P_74HC595::SEND_STATUS::COMPLETE, s2p.send());
    CHECK_EQUAL(FALSE, s2p.setSendData(0));
}

/**
* should be output clock.
*/
TEST(S2P_74HC595Test, should_be_output_clock)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(0);
    s2p.clear();

    for(int i=0; i<PARALLEL_OUTPUT_COUNT; i++)
    {
        s2p.send();
        CHECK(isPinOutput(3, LOW));
        s2p.send();
        CHECK(isPinOutput(3, HIGH));
    }
}

/**
* should be change status to sending.
*/
TEST(S2P_74HC595Test, should_be_change_status_to_sending)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(0);
    s2p.clear();
    checkClock(&s2p, 3);
}

/**
* should be change status to complete.
*/
TEST(S2P_74HC595Test, should_be_change_status_to_complete)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(0);
    s2p.clear();

    checkClock(&s2p, 3);

    CHECK_EQUAL(S2P_74HC595::SEND_STATUS::COMPLETE, s2p.send());
    CHECK(isPinOutput(3, LOW));
}

/**
* should be output low into serial pin when set 0.
*/
TEST(S2P_74HC595Test, should_be_output_low_into_serial_pin_when_set_0)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(0);
    s2p.clear();

    memset(expect_signals, LOW, sizeof(expect_signals));
    setOutputCallback(checkOutput, 3);

    checkClock(&s2p, 3);

    CHECK_EQUAL(S2P_74HC595::SEND_STATUS::COMPLETE, s2p.send());
    CHECK(isPinOutput(3, LOW));
    CHECK(8<=signal_counter);
}

/**
* should be send the data 1 when set the data 1.
*/
TEST(S2P_74HC595Test, should_be_send_the_data_1)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(1);
    s2p.clear();

    memset(expect_signals, LOW, sizeof(expect_signals));
    expect_signals[7] = HIGH;
    setOutputCallback(checkOutput, 3);

    checkClock(&s2p, 3);

    CHECK_EQUAL(S2P_74HC595::SEND_STATUS::COMPLETE, s2p.send());
    CHECK(isPinOutput(3, LOW));
    // CHECK(isPinOutput(4, HIGH));
    CHECK(8<=signal_counter);
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
