#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/MemoryUtility.h"

TEST_GROUP(MemoryUtility)
{
    void setup()
    {
    }

    void teardown()
    {
    }


};

/**
* should be clear byte array.
*/
TEST(MemoryUtility, should_be_clear_byte_array)
{
    BYTE array[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    BYTE expected[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    MemoryUtility::memclear(array, 8);
    MEMCMP_EQUAL(expected, array, 8);
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}