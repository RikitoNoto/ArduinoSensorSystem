#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/Dht11.h"
#include <Arduino.h>

TEST_GROUP(Dht11)
{
    Dht11* dht = nullptr;
    void setup()
    {
        setupSpyArduino();
    }

    void teardown()
    {
        delete dht;
        dht = nullptr;
    }

};

/**
* should be DATA to HIGH when start.
*/
TEST(Dht11, should_be_DATA_to_HIGH_when_start)
{
    dht = new Dht11(8);
    dht->start();
    CHECK(checkPinCalled(8, INPUT));
    CHECK(checkPinDigitalWrite(8, LOW));
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}