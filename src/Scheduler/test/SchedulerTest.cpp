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
    private:
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
    schedule = new ScheduleSpy(0);
    Scheduler::getInstance()->setSchedule(schedule);
    Scheduler::getInstance()->countTime();
    CHECK(schedule->is_called_execute);

}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}