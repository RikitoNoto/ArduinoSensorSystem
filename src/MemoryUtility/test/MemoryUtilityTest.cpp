#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/MemoryUtility.h"

TEST_GROUP(MemoryUtility)
{
    class A
    {
        public:
        BYTE aa;
    };

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
    MemoryUtility::memClear(array, 8);
    MEMCMP_EQUAL(expected, array, 8);
}

/**
* should be copy byte array.
*/
TEST(MemoryUtility, should_be_copy_byte_array)
{
    BYTE array[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    BYTE expected[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    MemoryUtility::memCopy(array, expected, 8);
    MEMCMP_EQUAL(expected, array, 8);
}

/**
* should be copy double array.
*/
TEST(MemoryUtility, should_be_copy_double_array)
{
    double array[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double expected[8] = {654.546498, 137867.4, 0.46579700, 96874.1, 02134.0, 65423, 1, 0};
    MemoryUtility::memCopy(array, expected, 8);
    MEMCMP_EQUAL(expected, array, 8);
}

/**
* should be copy class.
*/
TEST(MemoryUtility, should_be_copy_class)
{
    A a;
    A b;
    a.aa = 0xFF;
    MemoryUtility::memCopy(&b, &a, sizeof(A));
    MEMCMP_EQUAL(&a, &b, sizeof(A));
    CHECK_EQUAL(a.aa, b.aa);
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}