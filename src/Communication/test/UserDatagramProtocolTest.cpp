#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/UserDatagramProtocol.h"
#include "../src/Message_if.h"

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
bool EthernetUDP::is_called_stop = false;
bool EthernetUDP::is_called_beginPacket = false;
bool EthernetUDP::is_called_write = false;
bool EthernetUDP::is_called_endPacket = false;
uint8_t EthernetUDP::return_begin = 0;
uint16_t EthernetUDP::begin_arg_port_no = 0xFFFF;
int EthernetUDP::return_beginPacket = 1;
int EthernetUDP::return_endPacket = 1;

class TestMessage : public Message_if
{
public:
    virtual ~TestMessage(){;};
    virtual uint8_t* getData_uint8(void)
    {
        return nullptr;
    }

    virtual size_t getDataSize_sizet_uint8(void)
    {
        return 0;
    }
};

TEST_GROUP(UserDatagramProtocolTest)
{
    UserDatagramProtocol* instance;
    TestMessage* message;
    BYTE macAddress[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    void setup()
    {
        instance = nullptr;
        message = nullptr;
        Ethernet.setUp();
        EthernetUDP::setUp();
    }

    void teardown()
    {
        delete instance;
        delete message;
    }

    UserDatagramProtocol* callbeginCommunication(RESULT* result = nullptr, BYTE sspin = 10)
    {
        RESULT _result;
        UserDatagramProtocol* _instance = new UserDatagramProtocol(macAddress);
        _instance->setIpAddress(0xFF, 0xFF, 0xFF, 0xFF);
        _instance->setCsPinNo(sspin);
        _result = _instance->beginCommunication();
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
    instance = callbeginCommunication(&result);
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
    instance = callbeginCommunication(&result);
    CHECK_EQUAL(FAIL, result);
}

/**
* should be fail when link off.
*/
TEST(UserDatagramProtocolTest, should_be_fail_when_link_off)
{
    RESULT result = SUCCESS;
    Ethernet.return_link_status = EthernetLinkStatus::LinkOFF;
    instance = callbeginCommunication(&result);
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
    instance = callbeginCommunication(&result);
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
    instance = callbeginCommunication(&result);
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

    instance->beginCommunication();
    CHECK(EthernetUDP::is_called_begin);
    CHECK_EQUAL(3000, EthernetUDP::begin_arg_port_no);
}

/**
* should be call stop method when call endCommunication.
*/
TEST(UserDatagramProtocolTest, should_be_call_stop_method_when_call_end_communication)
{
    RESULT result = FAIL;
    EthernetUDP::begin_arg_port_no = 0;
    instance = callbeginCommunication(&result);
    instance->endCommunication();
    CHECK(EthernetUDP::is_called_stop);
}

/**
* should be call beginPacket method when call send data.
*/
TEST(UserDatagramProtocolTest, should_be_call_beginPacket_method_when_call_send_data)
{
    RESULT result = FAIL;
    WORD address[5] = {0};
    instance = callbeginCommunication(&result);
    message = new TestMessage;
    
    instance->sendData(message, address, 5);
    CHECK(EthernetUDP::is_called_beginPacket);
}

/**
* should be not call write method when fail beginPacket method.
*/
TEST(UserDatagramProtocolTest, should_be_not_call_write_method_when_return_0_beginPacket_method)
{
    RESULT result = SUCCESS;
    WORD address[5] = {0};
    instance = callbeginCommunication(&result);
    message = new TestMessage;
    
    EthernetUDP::return_beginPacket = 0;

    result = instance->sendData(message, address, 5);
    CHECK_FALSE(EthernetUDP::is_called_write);
    CHECK_EQUAL(FAIL, result);
}

/**
* should be call write method when success beginPacket method.
*/
TEST(UserDatagramProtocolTest, should_be_not_call_write_method_when_return_1_beginPacket_method)
{
    RESULT result = FAIL;
    WORD address[5] = {0};
    instance = callbeginCommunication();
    message = new TestMessage;
    
    EthernetUDP::return_beginPacket = 1;

    result = instance->sendData(message, address, 5);
    CHECK(EthernetUDP::is_called_write);
    CHECK_EQUAL(SUCCESS, result);
}

/**
* should be call endPacket method when call send data.
*/
TEST(UserDatagramProtocolTest, should_be_call_endPacket_method_when_call_send_data)
{
    RESULT result = FAIL;
    WORD address[5] = {0};
    instance = callbeginCommunication(&result);
    message = new TestMessage;
    
    instance->sendData(message, address, 5);
    CHECK(EthernetUDP::is_called_endPacket);
}

/**
* should be fail when endPacket return fail.
*/
TEST(UserDatagramProtocolTest, should_be_fail_when_endPacket_return_fail)
{
    RESULT result = SUCCESS;
    WORD address[5] = {0};
    instance = callbeginCommunication(&result);
    message = new TestMessage;
    
    EthernetUDP::return_endPacket = 0;
    result = instance->sendData(message, address, 5);
    CHECK_EQUAL(FAIL, result);
}

/**
* should be success when endPacket return success.
*/
TEST(UserDatagramProtocolTest, should_be_success_when_endPacket_return_success)
{
    RESULT result = FAIL;
    WORD address[5] = {0};
    instance = callbeginCommunication(&result);
    message = new TestMessage;
    
    EthernetUDP::return_endPacket = 1;
    result = instance->sendData(message, address, 5);
    CHECK_EQUAL(SUCCESS, result);
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}