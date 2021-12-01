#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/Point.h"

TEST_GROUP(Point)
{
    Point<int>* point_int;
    Point<double>* point_double;
    void setup()
    {

    }

    void teardown()
    {
        delete point_int;
        delete point_double;
    }
};


/**
* create instance of Point with integer.
*/
TEST(Point, should_be_create_two_int_args)
{
    point_int = new Point<int>(1,1);
}

/**
* create instance of Point with double.
*/
TEST(Point, should_be_create_two_double_args)
{
    point_double = new Point<double>(1.5,1.1);
}

/**
* should be access the member of x.
*/
TEST(Point, should_be_show_x)
{
    point_int = new Point<int>(1, 2);
    CHECK_EQUAL(1, point_int->getX());
}

/**
* should be access the member of y.
*/
TEST(Point, should_be_show_y)
{
    point_int = new Point<int>(1, 2);
    CHECK_EQUAL(2, point_int->getY());
}

/**
* should be set the member of x.
*/
TEST(Point, should_be_set_x)
{
    point_int = new Point<int>(1, 2);
    point_int->setX(10);
    CHECK_EQUAL(10, point_int->getX());
}

/**
* should be set the member of y.
*/
TEST(Point, should_be_set_y)
{
    point_int = new Point<int>(1, 2);
    point_int->setY(15);
    CHECK_EQUAL(15, point_int->getY());
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}