#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "CppUTestExt/MockSupport.h"

#include "../src/Timer.h"

#include "spy/Arduino.h"
static unsigned long return_value_millis;
static unsigned long return_value_micros;

unsigned long millis(void)
{
    return return_value_millis;
}

unsigned long micros(void)
{
    return return_value_micros;
}


TEST_GROUP(TimerTest)
{
    void setup()
    {
        return_value_millis = 0;
        return_value_micros = 0;
    }

    void teardown()
    {
    }
};

/**
* should be create instance.
*/
TEST(TimerTest, should_be_create_instance)
{
    Timer timer();
}

/**
* should be return time up zero seconds.
*/
TEST(TimerTest, should_be_return_time_up_zero_seconds_millis)
{
    Timer timer;
    // return value is 0.(to be not count.)
    return_value_millis = 0;
    timer.startCount();
    CHECK(timer.isTimeUpMillis(0));
}

/**
* should be not return time up one seconds.
*/
TEST(TimerTest, should_be_not_return_time_up_one_seconds_millis)
{
    Timer timer;
    return_value_millis = 0;
    timer.startCount();
    CHECK_FALSE(timer.isTimeUpMillis(1000));
}

/**
* should be return time up when time elapsed.
*/
TEST(TimerTest, should_be_return_time_up_when_time_elapsed_millis)
{
    Timer timer;
    return_value_millis = 100;
    timer.startCount();
    return_value_millis = 1000;
    CHECK(timer.isTimeUpMillis(900));
}

/**
* should be return time up zero seconds.
*/
TEST(TimerTest, should_be_return_time_up_zero_seconds_micros)
{
    Timer timer;
    // return value is 0.(to be not count.)
    return_value_micros = 0;
    timer.startCount();
    CHECK(timer.isTimeUpMicros(0));
}

/**
* should be not return time up one seconds.
*/
TEST(TimerTest, should_be_not_return_time_up_one_seconds_micros)
{
    Timer timer;
    // return value is 0.(to be not count.)
    return_value_micros = 0;
    timer.startCount();
    CHECK_FALSE(timer.isTimeUpMicros(1));
}

/**
* should be return time up when time elapsed.
*/
TEST(TimerTest, should_be_return_time_up_when_time_elapsed_micros)
{
    Timer timer;
    return_value_micros = 100;
    timer.startCount();
    return_value_micros = 1000;
    CHECK(timer.isTimeUpMicros(900));
}

/**
* should be elapsed time millis return 0 when not start.
*/
TEST(TimerTest, should_be_elapsed_time_millis_return_0_when_not_start)
{
    Timer timer;
    return_value_millis = 1000;
    CHECK_EQUAL(0, timer.getElapsedTimeMillis());
}

/**
* should be elpased time micros return 0 when not start.
*/
TEST(TimerTest, should_be_elpased_time_micros_return_0_when_not_start)
{
    Timer timer;
    return_value_micros = 1000;
    CHECK_EQUAL(0, timer.getElapsedTimeMicros());
}

/**
* should be elapsed time millis return 100 when elapse 100 second from start.
*/
TEST(TimerTest, should_be_elapsed_time_millis_return_100_when_elapse_100_second_from_start)
{
    Timer timer;
    return_value_millis = 1000;
    timer.startCount();
    return_value_millis = 1100;
    CHECK_EQUAL(100, timer.getElapsedTimeMillis());
}

/**
* should be elapsed time micros return 100 when elapse 100 second from start.
*/
TEST(TimerTest, should_be_elapsed_time_micros_return_100_when_elapse_100_second_from_start)
{
    Timer timer;
    return_value_micros = 1000;
    timer.startCount();
    return_value_micros = 1100;
    CHECK_EQUAL(100, timer.getElapsedTimeMicros());
}

/**
* should be elapsed time return 0 after stop count.
*/
TEST(TimerTest, should_be_elapsed_time_return_0_after_stop_count)
{
    Timer timer;
    return_value_millis = 1000;
    return_value_micros = 1000;
    timer.startCount();
    return_value_millis = 10000;
    return_value_micros = return_value_micros / 1000;

    timer.clearCount();
    CHECK_EQUAL(0, timer.getElapsedTimeMillis());
    CHECK_EQUAL(0, timer.getElapsedTimeMicros());
}

/**
* should be count when over flow millis.
*/
TEST(TimerTest, should_be_count_when_over_flow_millis)
{
    Timer timer;
    return_value_millis = 0xFFFFFFFFFFFFFFFF;
    timer.startCount();
    return_value_millis = 1000;
    CHECK_EQUAL(1001, timer.getElapsedTimeMillis());
}

/**
* should be count when over flow micros.
*/
TEST(TimerTest, should_be_count_when_over_flow_micros)
{
    Timer timer;
    return_value_micros = 0xFFFFFFFFFFFFFFFF;
    timer.startCount();
    return_value_micros = 1000;
    CHECK_EQUAL(1001, timer.getElapsedTimeMicros());
}

/**
* should be return elapsed time when timer pause.
*/
TEST(TimerTest, should_be_return_elapsed_time_when_timer_pause)
{
    Timer timer;
    return_value_micros = 1000;
    return_value_millis = return_value_micros / 1000;
    timer.startCount();
    return_value_micros = 2000;
    return_value_millis = return_value_micros / 1000;

    timer.pauseCount();
    CHECK_EQUAL(1, timer.getElapsedTimeMillis());
    CHECK_EQUAL(1000, timer.getElapsedTimeMicros());
}

/**
* should be not time up when timer pause and timer counting.
*/
TEST(TimerTest, should_be_not_time_up_when_timer_pause_and_timer_counting)
{
    Timer timer;
    return_value_micros = 1000;
    return_value_millis = return_value_micros / 1000;
    timer.startCount();
    return_value_micros = 2000;
    return_value_millis = return_value_micros / 1000;

    timer.pauseCount();

    return_value_micros = 10000;
    return_value_millis = return_value_micros / 1000;

    CHECK_EQUAL(FALSE, timer.isTimeUpMillis(2));
    CHECK_EQUAL(FALSE, timer.isTimeUpMicros(1001));
}

/**
* should be time up when timer pause and timer time up.
*/
TEST(TimerTest, should_be_time_up_when_timer_pause_and_timer_time_up)
{
    Timer timer;
    return_value_micros = 1000;
    return_value_millis = return_value_micros / 1000;
    timer.startCount();
    return_value_micros = 2000;
    return_value_millis = return_value_micros / 1000;

    timer.pauseCount();

    CHECK_EQUAL(TRUE, timer.isTimeUpMillis(1));
    CHECK_EQUAL(TRUE, timer.isTimeUpMicros(1000));
}

/**
* should be return elapsed time after restart timer.
*/
TEST(TimerTest, should_be_return_elapsed_time_after_restart_timer)
{
    Timer timer;
    return_value_micros = 0;
    return_value_millis = return_value_micros / 1000;
    timer.startCount();

    timer.pauseCount();
    timer.startCount();
    return_value_micros = 10000;
    return_value_millis = return_value_micros / 1000;

    CHECK_EQUAL(10000, timer.getElapsedTimeMicros());
    CHECK_EQUAL(10, timer.getElapsedTimeMillis());
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}