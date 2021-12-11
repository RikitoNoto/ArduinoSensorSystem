#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include "../src/EthernetBase.h"

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


// TEST_GROUP(EthernetBaseTest)
// {
//     EthernetBase* instance;
//     BYTE macAddress[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
//     void setup()
//     {
//         instance = new EthernetBase(macAddress);
//     }

//     void teardown()
//     {
//         delete instance;
//     }

//     void createInstance(BYTE* _macAddress)
//     {
//         if(_macAddress == nullptr)
//         {
//             instance = new EthernetBase(macAddress);
//         }
//         else
//         {
//             instance = new EthernetBase(_macAddress);
//         }
//     }

//     bool isSameIpAddress(const EthernetBase::IpAddressV4* ipAddress1, const EthernetBase::IpAddressV4* ipAddress2)
//     {
//         bool result = false;
//         if(ipAddress1 != nullptr && ipAddress2 != nullptr)
//         {
//             if( (ipAddress1->m_octet1 == ipAddress2->m_octet1) &&
//                 (ipAddress1->m_octet2 == ipAddress2->m_octet2) &&
//                 (ipAddress1->m_octet3 == ipAddress2->m_octet3) &&
//                 (ipAddress1->m_octet4 == ipAddress2->m_octet4))
//                 {
//                     result = true;
//                 }
//         }
        
//         return result;
//     }

//     bool isSameMacAddress(const BYTE* ipAddress1, const EthernetBase::IpAddressV4* ipAddress2)
//     {
//         bool result = false;
//         if(ipAddress1 != nullptr && ipAddress2 != nullptr)
//         {
//             if( (ipAddress1->m_octet1 == ipAddress2->m_octet1) &&
//                 (ipAddress1->m_octet2 == ipAddress2->m_octet2) &&
//                 (ipAddress1->m_octet3 == ipAddress2->m_octet3) &&
//                 (ipAddress1->m_octet4 == ipAddress2->m_octet4))
//                 {
//                     result = true;
//                 }
//         }
        
//         return result;
//     }
// };

// // /**
// // * create instance of EthernetBase.
// // */
// // TEST(EthernetBaseTest, should_be_create_instance_with_mac_address)
// // {
// //     instance = new EthernetBase(macAddress);
// // }

// /**
// * should be set and get ip address.
// */
// TEST(EthernetBaseTest, should_be_set_and_get_ip_address)
// {
//     EthernetBase::IpAddressV4 expectedIPAddress = {192, 168, 1, 1};
//     instance->setIpAddress(192, 168, 1, 1);
//     CHECK(isSameIpAddress(instance->getIpAddress(), &expectedIPAddress));
// }

// /**
// * should be set and get mac address.
// */
// TEST(EthernetBaseTest, should_be_set_and_get_mac_address)
// {
//     instance->setMacAddress(192, 168, 1, 1);
//     CHECK(isSameIpAddress(instance->getIpAddress(), &expectedIPAddress));
// }


int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}