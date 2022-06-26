#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

#define TEST_SOURCE 1

#include "../src/Dht11.h"
#include <Arduino.h>
#include <Timer.h>
#include <DHT.h>

TEST_GROUP(Dht11Test)
{
    void setup()
    {
        setupSpyArduino();
        Timer::setup();
    }

    void teardown()
    {
    }
};

/**
* should be create a instance.
*/
TEST(Dht11Test, should_be_create_a_instance)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    delete dht;
}

/**
* should be called constructor with pin.
*/
TEST(Dht11Test, should_be_called_constructor_with_pin)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    CHECK_EQUAL(8, dht->m_dht->m_pin);
    delete dht;
}

/**
* should be called constructor with type.
*/
TEST(Dht11Test, should_be_called_constructor_with_type)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    CHECK_EQUAL(DHT11, dht->m_dht->m_type);
    delete dht;
}

/**
* should be did not call begin when not start.
*/
TEST(Dht11Test, should_be_didnt_call_begin_when_not_start)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    CHECK_FALSE(dht->m_dht->is_called_begin);
    delete dht;
}

/**
* should be called begin when start.
*/
TEST(Dht11Test, should_be_called_begin_when_start)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    Timer::setElapsedTimeMillis(2000);
    dht->start();
    CHECK(dht->m_dht->is_called_begin);
    delete dht;
}

/**
* should be read temperature 0.
*/
TEST(Dht11Test, should_be_read_temperature_0)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    Timer::setElapsedTimeMillis(2000);
    dht->m_dht->temperature = 0;

    dht->start();
    dht->execute();
    CHECK_EQUAL(0, dht->getData());
    delete dht;
}

/**
* should be read temperature 1.
*/
TEST(Dht11Test, should_be_read_temperature_1)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    Timer::setElapsedTimeMillis(2000);
    dht->m_dht->temperature = 1.0;

    dht->start();
    dht->execute();
    CHECK_EQUAL(1000, dht->getData());
    delete dht;
}

/**
* should be read twice.
*/
TEST(Dht11Test, should_be_read_twice)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    Timer::setElapsedTimeMillis(2000);
    dht->m_dht->temperature = 1.0;

    CHECK_EQUAL(SUCCESS, dht->start());
    dht->execute();
    CHECK_EQUAL(1000, dht->getData());

    Timer::elapseTimeMillis(2000);
    dht->m_dht->temperature = 2.0;

    CHECK_EQUAL(SUCCESS, dht->start());
    dht->execute();
    CHECK_EQUAL(2000, dht->getData());
    delete dht;
}

/**
* should be do not read twice after less than 2s from first.
*/
TEST(Dht11Test, should_be_read_twice_after_less_than_2s_from_first)
{
    Dht11* dht = new Dht11(/*data pin*/8);
    Timer::setElapsedTimeMillis(2000);
    dht->m_dht->temperature = 1.0;

    CHECK_EQUAL(SUCCESS, dht->start());
    dht->execute();
    CHECK_EQUAL(1000, dht->getData());

    dht->m_dht->temperature = 2.0;

    CHECK_EQUAL(FAIL, dht->start());
    delete dht;
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}