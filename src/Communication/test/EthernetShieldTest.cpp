#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
// #include "../src/EthernetShield.h"

TEST_GROUP(EthernetShield)
{
    // EthernetShield* instance;
    void setup()
    {
    }

    void teardown()
    {
        // delete instance;
    }
};

// /**
// * create instance of EthernetShield.
// */
// TEST(EthernetShield, should_be_create_instance_with_mac_address)
// {
//     char macAddress[] = "AAAAAAAAAAAA";
//     instance = new EthernetShield(macAddress);
// }


int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}