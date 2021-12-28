#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/UserDatagramProtocol.h"

#include "spy/Ethernet.h"
#include "spy/EthernetUdp.h"

EthernetHardwareStatus EthernetClass::return_hardware_value = EthernetHardwareStatus::EthernetW5100;
EthernetLinkStatus EthernetClass::return_link_status = EthernetLinkStatus::LinkON;
bool EthernetClass::isCalledBegin = false;
bool EthernetClass::isCalledInit = false;
uint8_t* EthernetClass::spy_mac = nullptr;
uint8_t EthernetClass::cspin = 0;
IPAddress EthernetClass::spy_ip = IPAddress();
EthernetClass Ethernet;


bool EthernetUDP::is_called_begin = false;
uint8_t EthernetUDP::return_begin = 0;
uint16_t EthernetUDP::begin_arg_port_no = 0xFFFF;

TEST_GROUP(UserDatagramProtocolTest)
{
    UserDatagramProtocol* instance;
    BYTE macAddress[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    void setup()
    {
        instance = nullptr;
        Ethernet.setUp();
        EthernetUDP::setUp();
    }

    void teardown()
    {
        delete instance;
    }

    UserDatagramProtocol* callBegin(RESULT* result = nullptr, BYTE sspin = 10)
    {
        RESULT _result;
        UserDatagramProtocol* _instance = new UserDatagramProtocol(macAddress);
        _instance->setIpAddress(0xFF, 0xFF, 0xFF, 0xFF);
        _instance->setCsPinNo(sspin);
        _result = _instance->begin();
        if(nullptr != result)
        {
            *result = _result;
        }
        return _instance;
    }
};

/**
* create instance of UserDatagramProtocol with no args.
*/
TEST(UserDatagramProtocolTest, should_be_create_instance_with_with_no_args)
{
    instance = new UserDatagramProtocol;
}

/**
* create instance of UserDatagramProtocol.
*/
TEST(UserDatagramProtocolTest, should_be_create_instance_with_mac_address)
{
    instance = new UserDatagramProtocol(macAddress);
    BYTE test_mac_address[] = {0, 0, 0, 0, 0, 0};
    instance->getMacAddress(test_mac_address);
    MEMCMP_EQUAL(macAddress, test_mac_address, sizeof(BYTE) * 6);
}

/**
* create instance of UserDatagramProtocol by args.
*/
TEST(UserDatagramProtocolTest, should_be_create_instance_with_mac_address_by_args)
{
    instance = new UserDatagramProtocol(macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
    BYTE test_mac_address[] = {0, 0, 0, 0, 0, 0};
    instance->getMacAddress(test_mac_address);
    MEMCMP_EQUAL(macAddress, test_mac_address, sizeof(BYTE) * 6);
}

/**
* should be set and get ip address.
*/
TEST(UserDatagramProtocolTest, should_be_set_and_get_ip_address)
{
    instance = new UserDatagramProtocol;
    BYTE expected_address[] = {192, 168, 1, 1};
    instance->setIpAddress(192, 168, 1, 1);
    MEMCMP_EQUAL(expected_address, instance->getIpAddress()->getAddress(), 4);
}

/**
* should be return success when call begin method.
*/
TEST(UserDatagramProtocolTest, should_be_return_success_when_call_begin_method)
{
    RESULT result = FAIL;
    instance = callBegin(&result);
    CHECK(Ethernet.isCalledInit);
    CHECK_EQUAL(SUCCESS, result);
}

/**
* should be fail when no hardware.
*/
TEST(UserDatagramProtocolTest, should_be_fail_when_no_hardware)
{
    RESULT result = SUCCESS;
    Ethernet.return_hardware_value = EthernetNoHardware;
    instance = callBegin(&result);
    CHECK_EQUAL(FAIL, result);
}

/**
* should be fail when link off.
*/
TEST(UserDatagramProtocolTest, should_be_fail_when_link_off)
{
    RESULT result = SUCCESS;
    Ethernet.return_link_status = EthernetLinkStatus::LinkOFF;
    instance = callBegin(&result);
    CHECK_EQUAL(FAIL, result);
}

/**
* should be set and get read port.
*/
TEST(UserDatagramProtocolTest, should_be_set_and_get_read_port)
{
    instance = new UserDatagramProtocol;
    instance->setReadPort(1234);
    CHECK_EQUAL(1234, instance->getReadPort());
}

/**
* should be call begin method with default port when not set read port.
*/
TEST(UserDatagramProtocolTest, should_be_call_begin_method_with_default_port_when_not_set_read_port)
{
    RESULT result = FAIL;
    EthernetUDP::begin_arg_port_no = 0;
    instance = callBegin(&result);
    CHECK(EthernetUDP::is_called_begin);
    CHECK_EQUAL(0xFFFF, EthernetUDP::begin_arg_port_no);
}

/**
* should be fail when begin method return 0.
*/
TEST(UserDatagramProtocolTest, should_be_fail_when_begin_method_return_0)
{
    RESULT result = SUCCESS;
    EthernetUDP::return_begin = 0;
    instance = callBegin(&result);
    CHECK_EQUAL(FAIL, result);
}

/**
* should be call begin method when set read port.
*/
TEST(UserDatagramProtocolTest, should_be_call_begin_method_of_udp_when_set_read_port)
{
    instance = new UserDatagramProtocol(macAddress);
    instance->setIpAddress(0xFF, 0xFF, 0xFF, 0xFF);
    instance->setCsPinNo(10);
    instance->setReadPort(3000);

    instance->begin();
    CHECK(EthernetUDP::is_called_begin);
    CHECK_EQUAL(3000, EthernetUDP::begin_arg_port_no);
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}