#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "CppUTestExt/MockSupport.h"
#include "../src/EthernetBase.h"

class TempEthernetBase : public EthernetBase
{
public:
    TempEthernetBase():EthernetBase(){};
    TempEthernetBase(BYTE* mac_address):EthernetBase(mac_address){};
    TempEthernetBase(BYTE octet1, BYTE octet2, BYTE octet3, BYTE octet4, BYTE octet5, BYTE octet6):EthernetBase(octet1, octet2, octet3, octet4, octet5, octet6){};
    virtual RESULT sendData(const Message_if* data){return FAIL;};  // send data.
    virtual RESULT receiveData(Message_if* data){return FAIL;};    // receive data.
    RESULT end();
};

#include "spy/Ethernet.h"

TEST_GROUP(IpAddressTest)
{
    void setup()
    {
    }

    void teardown()
    {
    }    

    bool isSameIpAddress(const BYTE* ipAddress1, const BYTE* ipAddress2, BYTE size)
    {
        for(BYTE i=0; i<size; i++)
        {
            if(ipAddress1[i] != ipAddress2[i])
            {
                return false;
            }
        }

        return true;
    }
};

/**
* should be create the instance of none version.
*/
TEST(IpAddressTest, should_be_create_instance_none_version)
{
    EthernetBase::IpAddress ipaddress;
    CHECK_EQUAL(EthernetBase::IpAddress::NONE_VERSION, ipaddress.getVersion());
}

/**
* should be create the instance of version 4.
*/
TEST(IpAddressTest, should_be_create_instance_version4)
{
    EthernetBase::IpAddress ipaddress_v4(0xFF, 0xFF, 0xFF, 0xFF);
    CHECK_EQUAL(EthernetBase::IpAddress::VERSION4, ipaddress_v4.getVersion());
}

/**
* should be create the instance of version 6.
*/
TEST(IpAddressTest, should_be_create_instance_version6)
{
    EthernetBase::IpAddress ipaddress_v6(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    CHECK_EQUAL(EthernetBase::IpAddress::VERSION6, ipaddress_v6.getVersion());
}

/**
* should be set null address when create default constructor.
*/
TEST(IpAddressTest, should_be_set_null_address_default_constructor)
{
    EthernetBase::IpAddress ipaddress;
    POINTERS_EQUAL(nullptr, ipaddress.getAddress());
}

/**
* should be set ip address when create version4 constructor.
*/
TEST(IpAddressTest, should_be_set_ip_address_version4_constructor)
{
    EthernetBase::IpAddress ipaddress(0x01, 0x02, 0x03, 0x04);
    BYTE expected_address[] = {0x01, 0x02, 0x03, 0x04};
    CHECK(isSameIpAddress(expected_address, ipaddress.getAddress(), static_cast<BYTE>(4)));
}

/**
* should be get version4.
*/
TEST(IpAddressTest, should_be_get_version4)
{
    EthernetBase::IpAddress ipaddress(0x01, 0x02, 0x03, 0x04);
    CHECK_EQUAL(EthernetBase::IpAddress::VERSION::VERSION4, ipaddress.getVersion());
}

/**
* should be get version6.
*/
TEST(IpAddressTest, should_be_get_version6)
{
    EthernetBase::IpAddress ipaddress(0x01, 0x02, 0x03, 0x04, 0x05, 0x06);
    CHECK_EQUAL(EthernetBase::IpAddress::VERSION::VERSION6, ipaddress.getVersion());
}

/**
* should be set ip address when create version6 constructor.
*/
TEST(IpAddressTest, should_be_set_ip_address_version6_constructor)
{
    EthernetBase::IpAddress ipaddress(0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A);
    BYTE expected_address[] = {0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A};
    CHECK(isSameIpAddress(expected_address, ipaddress.getAddress(), static_cast<BYTE>(6)));
}

/**
* should be change the different ip address, to version6 from version4.
*/
TEST(IpAddressTest, should_be_change_ip_address_to_version6_from_version4)
{
    EthernetBase::IpAddress ipaddress(0x0F, 0x0E, 0x0D, 0x0C);
    BYTE expected_address[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    ipaddress.setAddress(0x11, 0x22, 0x33, 0x44, 0x55, 0x66);
    CHECK(isSameIpAddress(expected_address, ipaddress.getAddress(), static_cast<BYTE>(6)));
}

/**
* should be change the different ip address, to version4 from version6.
*/
TEST(IpAddressTest, should_be_change_ip_address_to_version4_from_version6)
{
    EthernetBase::IpAddress ipaddress(0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A);
    BYTE expected_address[] = {0x64, 0x87, 0x41, 0x23};
    ipaddress.setAddress(0x64, 0x87, 0x41, 0x23);
    CHECK(isSameIpAddress(expected_address, ipaddress.getAddress(), static_cast<BYTE>(4)));
}

/**
* should be convert to arduino ip address class.
*/
TEST(IpAddressTest, should_be_convert_to_arduino_ip_address_class)
{
    EthernetBase::IpAddress ipaddress(0x0F, 0x0E, 0x0D, 0x0C);
    IPAddress expected_ipaddress(0x0F, 0x0E, 0x0D, 0x0C);
    
    MEMCMP_EQUAL(&expected_ipaddress, ipaddress.getArduinoClass(), sizeof(IPAddress));
}

//###########
// Ethernet test
//###########

EthernetHardwareStatus EthernetClass::return_hardware_value = EthernetHardwareStatus::EthernetW5100;
EthernetLinkStatus EthernetClass::return_link_status = EthernetLinkStatus::LinkON;
bool EthernetClass::isCalledBegin = false;
bool EthernetClass::isCalledInit = false;
uint8_t* EthernetClass::spy_mac = nullptr;
uint8_t EthernetClass::cspin = 0;
IPAddress EthernetClass::spy_ip = IPAddress();
EthernetClass Ethernet;

TEST_GROUP(EthernetBaseTest)
{
    EthernetBase* instance;
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

    EthernetBase* callBegin(RESULT* result = nullptr, BYTE sspin = 10)
    {
        RESULT _result;
        EthernetBase* _instance = new TempEthernetBase(macAddress);
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
* create instance of EthernetBase.
*/
TEST(EthernetBaseTest, should_be_create_instance_with_mac_address)
{
    instance = new TempEthernetBase(macAddress);
}

/**
* create instance of EthernetBase by args.
*/
TEST(EthernetBaseTest, should_be_create_instance_with_mac_address_by_args)
{
    instance = new TempEthernetBase(macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}

/**
* should be set mac address by constructor.
*/
TEST(EthernetBaseTest, should_be_set_mac_address_by_constructor)
{
    instance = new TempEthernetBase(macAddress);
    BYTE test_mac_address[] = {0, 0, 0, 0, 0, 0};
    instance->getMacAddress(test_mac_address);
    MEMCMP_EQUAL(macAddress, test_mac_address, sizeof(BYTE) * 6);
}

/**
* should be set mac address by constructor of args.
*/
TEST(EthernetBaseTest, should_be_set_mac_address_by_constructor_of_args)
{
    instance = new TempEthernetBase(0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F);
    BYTE expected_address[] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    BYTE test_mac_address[] = {0, 0, 0, 0, 0, 0};
    instance->getMacAddress(test_mac_address);
    MEMCMP_EQUAL(expected_address, test_mac_address, sizeof(BYTE) * 6);
}

/**
* should be get mac address.
*/
TEST(EthernetBaseTest, should_be_get_mac_address)
{
    instance = new TempEthernetBase(macAddress);
    BYTE* test_mac_address = nullptr;
    test_mac_address = instance->getMacAddress();
    MEMCMP_EQUAL(macAddress, test_mac_address, sizeof(BYTE) * 6);
}

/**
* should be set mac address by instance method.
*/
TEST(EthernetBaseTest, should_be_set_mac_address_by_instance_method)
{
    instance = new TempEthernetBase(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    BYTE expected_address[] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    BYTE test_mac_address[] = {0, 0, 0, 0, 0, 0};
    instance->setMacAddress(expected_address);
    instance->getMacAddress(test_mac_address);
    MEMCMP_EQUAL(expected_address, test_mac_address, sizeof(BYTE) * 6);
}

/**
* should be set mac address by instance method with 6 args.
*/
TEST(EthernetBaseTest, should_be_set_mac_address_by_instance_method_with_6args)
{
    instance = new TempEthernetBase(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    BYTE expected_address[] = {0x05, 0x46, 0x19, 0x4D, 0xE7, 0xFF};
    BYTE test_mac_address[] = {0, 0, 0, 0, 0, 0};
    instance->setMacAddress(0x05, 0x46, 0x19, 0x4D, 0xE7, 0xFF);
    instance->getMacAddress(test_mac_address);
    MEMCMP_EQUAL(expected_address, test_mac_address, sizeof(BYTE) * 6);
}

/**
* should be set noHardWare default in cs pin.
*/
TEST(EthernetBaseTest, should_be_set_noHardware_default_in_cs_pin)
{
    instance = new TempEthernetBase;
    CHECK_EQUAL(EthernetBase::HARDWARE_CSPIN::NONE_HARDWARE, instance->getCsPinNo());
}

/**
* should be set and get cs pin.
*/
TEST(EthernetBaseTest, should_be_set_and_get_cs_pin)
{
    instance = new TempEthernetBase;
    instance->setCsPinNo(EthernetBase::HARDWARE_CSPIN::ARDUINO_SHIELD);
    CHECK_EQUAL(EthernetBase::HARDWARE_CSPIN::ARDUINO_SHIELD, instance->getCsPinNo());
}

/**
* should be set and get ip address.
*/
TEST(EthernetBaseTest, should_be_set_and_get_ip_address)
{
    instance = new TempEthernetBase;
    BYTE expected_address[] = {192, 168, 1, 1};
    instance->setIpAddress(192, 168, 1, 1);
    MEMCMP_EQUAL(expected_address, instance->getIpAddress()->getAddress(), 4);
}

/**
* should be set and get ip address by ipaddress instance.
*/
TEST(EthernetBaseTest, should_be_set_and_get_ip_address_by_ipaddress_instance)
{
    instance = new TempEthernetBase;
    EthernetBase::IpAddress ipaddress(0xFF, 0xEE, 0xDD, 0xCC);
    BYTE expected_address[] = {0xFF, 0xEE, 0xDD, 0xCC};
    instance->setIpAddress(&ipaddress);
    MEMCMP_EQUAL(expected_address, instance->getIpAddress()->getAddress(), 4);
}

/**
* should not be call begin method with no ip address.
*/
TEST(EthernetBaseTest, should_not_be_call_begin_method_with_no_ip_address)
{
    instance = new TempEthernetBase;
    instance->begin();
    CHECK_FALSE(Ethernet.isCalledBegin);
}

/**
* should be call begin method.
*/
TEST(EthernetBaseTest, should_be_call_begin_method)
{
    instance = callBegin();
    CHECK(Ethernet.isCalledBegin);
}

/**
* should be return fail when did not call begin method.
*/
TEST(EthernetBaseTest, should_be_return_fail_when_did_not_call_begin_method)
{
    RESULT result = SUCCESS;
    instance = new TempEthernetBase;
    result = instance->begin();
    CHECK_EQUAL(FAIL, result);
}

/**
* should be return success when call begin method.
*/
TEST(EthernetBaseTest, should_be_return_success_when_call_begin_method)
{
    RESULT result = FAIL;
    instance = callBegin(&result);
    CHECK_EQUAL(SUCCESS, result);
}

/**
* should be call init method when call begin method.
*/
TEST(EthernetBaseTest, should_be_call_init_method_when_call_begin_method)
{
    instance = callBegin();
    CHECK(Ethernet.isCalledInit);
}

/**
* should be call init method with any number.
*/
TEST(EthernetBaseTest, should_be_call_init_method_with_any_number)
{
    instance = callBegin(nullptr, 50);
    CHECK(Ethernet.isCalledInit);
    CHECK_EQUAL(50, Ethernet.cspin);
}

/**
* should be fail when no hardware.
*/
TEST(EthernetBaseTest, should_be_fail_when_no_hardware)
{
    RESULT result = SUCCESS;
    Ethernet.return_hardware_value = EthernetNoHardware;
    instance = callBegin(&result);
    CHECK_EQUAL(FAIL, result);
}

/**
* should be fail when link off.
*/
TEST(EthernetBaseTest, should_be_fail_when_link_off)
{
    RESULT result = SUCCESS;
    Ethernet.return_link_status = EthernetLinkStatus::LinkOFF;
    instance = callBegin(&result);
    CHECK_EQUAL(FAIL, result);
}

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}