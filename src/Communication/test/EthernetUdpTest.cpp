#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/EthernetUdp.h"

TEST_GROUP(EthernetUdp)
{
    EthernetUdp* instance;
    BYTE macAddress[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    void setup()
    {
        instance = nullptr;
        Ethernet.setUp();
    }

    void teardown()
    {
        delete instance;
    }
};

/**
* create instance of EthernetUdp.
*/
TEST(EthernetUdp, should_be_create_instance)
{
}


int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}