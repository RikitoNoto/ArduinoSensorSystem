#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <Arduino.h>
#include "S2P_74HC595.h"

TEST_GROUP(S2P_74HC595Test)
{
    static const BYTE PARALLEL_OUTPUT_COUNT = 8;
    void setup()
    {
        setupSpyArduino();
    }

    void teardown()
    {
    }
};

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

    CHECK(isPinCalled(3, OUTPUT));
    CHECK(isPinCalled(4, OUTPUT));
    CHECK(isPinCalled(5, OUTPUT));
}

/**
* should be set the pins as output.
*/
TEST(S2P_74HC595Test, should_be_set_the_pins_as_output2)
{
    S2P_74HC595 s2p(/*SER*/ 6, /*SRCLK*/ 7, /*SRCLR*/ 8);

    CHECK(isPinCalled(6, OUTPUT));
    CHECK(isPinCalled(7, OUTPUT));
    CHECK(isPinCalled(8, OUTPUT));
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
    CHECK(isPinDigitalWrite(5, HIGH));
}

/**
* should be not output clear pin when it is not clear output.
*/
TEST(S2P_74HC595Test, should_be_not_output_clear_pin_when_not_clear_output)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    CHECK(isPinDigitalWrite(5, HIGH));
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
    CHECK(isPinDigitalWrite(4, LOW));
}

// /**
// * should be not able to set data for sending.
// */
// TEST(S2P_74HC595Test, should_be_not_able_to_set_data_for_sending)
// {
//     S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
//     CHECK_EQUAL(TRUE, s2p.setSendData(0));
//     for(int i=0; i<PARALLEL_OUTPUT_COUNT; i++)
//     {
//         s2p.send();
//         CHECK_EQUAL(FALSE, s2p.setSendData(0));
//     }
// }

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
        CHECK(isPinDigitalWrite(3, LOW));
        s2p.send();
        CHECK(isPinDigitalWrite(3, HIGH));
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
    for(int i=0; i<PARALLEL_OUTPUT_COUNT; i++)
    {
        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK(isPinDigitalWrite(3, LOW));

        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK(isPinDigitalWrite(3, HIGH));
    }
}

/**
* should be change status to complete.
*/
TEST(S2P_74HC595Test, should_be_change_status_to_complete)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(0);
    s2p.clear();

    for(int i=0; i<PARALLEL_OUTPUT_COUNT; i++)
    {
        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK(isPinDigitalWrite(3, LOW));

        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK(isPinDigitalWrite(3, HIGH));
    }

    CHECK_EQUAL(S2P_74HC595::SEND_STATUS::COMPLETE, s2p.send());
    CHECK(isPinDigitalWrite(3, LOW));
}

/**
* should be output low into serial pin when set 0.
*/
TEST(S2P_74HC595Test, should_be_output_low_into_serial_pin_when_set_0)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(0);
    s2p.clear();

    for(int i=0; i<PARALLEL_OUTPUT_COUNT; i++)
    {
        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK(isPinDigitalWrite(3, LOW));

        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK(isPinDigitalWrite(3, HIGH));

        CHECK(isPinDigitalWrite(4, LOW));
    }

    CHECK_EQUAL(S2P_74HC595::SEND_STATUS::COMPLETE, s2p.send());
    CHECK(isPinDigitalWrite(3, LOW));
}

/**
* should be send the data 1 when set the data 1.
*/
TEST(S2P_74HC595Test, should_be_send_the_data_1)
{
    S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
    s2p.setSendData(1);
    s2p.clear();

    for(int i=0; i<PARALLEL_OUTPUT_COUNT; i++)
    {
        if(i!=0)
        {
            CHECK(isPinDigitalWrite(4, LOW));
        }
        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK(isPinDigitalWrite(3, LOW));

        CHECK_EQUAL(S2P_74HC595::SEND_STATUS::SENDING, s2p.send());
        CHECK(isPinDigitalWrite(3, HIGH));
    }

    CHECK_EQUAL(S2P_74HC595::SEND_STATUS::COMPLETE, s2p.send());
    CHECK(isPinDigitalWrite(3, LOW));
    CHECK(isPinDigitalWrite(4, HIGH));
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
