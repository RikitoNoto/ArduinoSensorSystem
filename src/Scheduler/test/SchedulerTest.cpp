#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/Scheduler.h"

TEST_GROUP(SchedulerTest)
{
    class ScheduleSpy : public Schedule_if
    {
    public:
        ScheduleSpy(DWORD ms=0)
        {
            this->m_ms = ms;
            this->is_called_execute = false;
        }

        virtual ~ScheduleSpy()
        {

        }

        void execute(void)
        {
            this->is_called_execute = true;
        }

        DWORD getTime(void)
        {
            return this->m_ms;
        }

        SchduleType getScheduleType(void)
        {
            return SchduleType::INTERVAL;
        }

        bool is_called_execute;
        DWORD m_ms;
    };

    ScheduleSpy* schedule = nullptr;

    void setup()
    {
    }

    void teardown()
    {
        Scheduler::deleteInstance();
        delete schedule;
    }

    /**
    * check to call the func after the ms,
    * and check to be not call the func before the ms.
    */
    void checkCalledFuncWithTime(Scheduler::count_t ms, Scheduler::count_t check_time)
    {
        schedule = new ScheduleSpy(ms);
        Scheduler::sid_t id = Scheduler::getInstance()->setSchedule(schedule);
        Scheduler::getInstance()->start(id);

        // check to call func each 1ms.
        for(Scheduler::count_t passed_time=1; passed_time<=check_time ; passed_time++)
        {
            Scheduler::getInstance()->count1ms();
            // if it is same the passed time and ms.
            if( (passed_time%ms) == 0)
            {
                CHECK(schedule->is_called_execute);
                schedule->is_called_execute = false;
            }
            else
            {
                CHECK_FALSE(schedule->is_called_execute);
            }

        }
    }
};

/**
* shoule be able to set schedule.
*/
TEST(SchedulerTest, shoule_be_able_to_set_schedule)
{
    schedule = new ScheduleSpy();
    Scheduler::getInstance()->setSchedule(schedule);
}

/**
* shoule be call immediately the func with 0ms.
*/
TEST(SchedulerTest, shoule_be_call_immediately_the_func_with_0ms)
{
    checkCalledFuncWithTime(0, 0);
}

/**
* shoule be call the func after 10ms.
*/
TEST(SchedulerTest, shoule_be_call_the_func_after_10ms)
{
    checkCalledFuncWithTime(10, 10);
}

/**
* shoule be call the func after 10ms and 20ms.
*/
TEST(SchedulerTest, shoule_be_call_the_func_after_10ms_and_20ms)
{
    checkCalledFuncWithTime(10, 20);
}

/**
* shoule be call immediately the two funcs with 0ms.
*/
TEST(SchedulerTest, shoule_be_call_the_two_funcs_with_0ms)
{
    ScheduleSpy* schedule1 = new ScheduleSpy(0);
    Scheduler::sid_t id1 = Scheduler::getInstance()->setSchedule(schedule1);


    ScheduleSpy* schedule2 = new ScheduleSpy(0);
    Scheduler::sid_t id2 = Scheduler::getInstance()->setSchedule(schedule2);

    Scheduler::getInstance()->start(id1);
    Scheduler::getInstance()->start(id2);

    Scheduler::getInstance()->count1ms();
    CHECK(schedule1->is_called_execute);
    CHECK(schedule2->is_called_execute);

    delete schedule1;
    delete schedule2;
}

/**
* shoule be call the two funcs after 5ms and 3ms.
*/
TEST(SchedulerTest, shoule_be_call_the_two_func_after_5ms_and_3ms)
{
    ScheduleSpy* schedule1 = new ScheduleSpy(5);
    Scheduler::sid_t id1 = Scheduler::getInstance()->setSchedule(schedule1);

    ScheduleSpy* schedule2 = new ScheduleSpy(3);
    Scheduler::sid_t id2 = Scheduler::getInstance()->setSchedule(schedule2);

    Scheduler::getInstance()->start(id1);
    Scheduler::getInstance()->start(id2);

    Scheduler::getInstance()->count1ms();
    CHECK_FALSE(schedule1->is_called_execute);
    CHECK_FALSE(schedule2->is_called_execute);
    schedule1->is_called_execute = false;
    schedule2->is_called_execute = false;
    Scheduler::getInstance()->count1ms();
    CHECK_FALSE(schedule1->is_called_execute);
    CHECK_FALSE(schedule2->is_called_execute);
    schedule1->is_called_execute = false;
    schedule2->is_called_execute = false;
    Scheduler::getInstance()->count1ms();
    CHECK_FALSE(schedule1->is_called_execute);
    CHECK(schedule2->is_called_execute);
    schedule1->is_called_execute = false;
    schedule2->is_called_execute = false;
    Scheduler::getInstance()->count1ms();
    CHECK_FALSE(schedule1->is_called_execute);
    CHECK_FALSE(schedule2->is_called_execute);
    schedule1->is_called_execute = false;
    schedule2->is_called_execute = false;
    Scheduler::getInstance()->count1ms();
    CHECK(schedule1->is_called_execute);
    CHECK_FALSE(schedule2->is_called_execute);
    schedule1->is_called_execute = false;
    schedule2->is_called_execute = false;
    delete schedule1;
    delete schedule2;
}

/**
* shoule be not call immediately the func that do not start.
*/
TEST(SchedulerTest, shoule_be_not_call_the_func_that_do_not_start)
{
    ScheduleSpy* schedule1 = new ScheduleSpy(0);
    Scheduler::sid_t id1 = Scheduler::getInstance()->setSchedule(schedule1);


    ScheduleSpy* schedule2 = new ScheduleSpy(0);
    Scheduler::getInstance()->setSchedule(schedule2);

    Scheduler::getInstance()->start(id1);

    Scheduler::getInstance()->count1ms();
    CHECK(schedule1->is_called_execute);
    CHECK_FALSE(schedule2->is_called_execute);

    delete schedule1;
    delete schedule2;
}

/**
* shoule be use the MSTimer2.
*/
TEST(SchedulerTest, shoule_be_use_the_MSTimer2)
{
    // ScheduleSpy* schedule2 = new ScheduleSpy(3);
    // Scheduler::getInstance()->setSchedule(schedule2);
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}