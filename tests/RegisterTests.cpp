
#include <catch2/catch_all.hpp>
#include <iostream>

#include "Bitfield.hpp"
#include "Register.hpp"
#include "Types.hpp"

namespace Svd2cppObjects
{
    namespace MyRegister
    {

        struct register1
        {
            Svd2cppObjects::Bitfield<24, 8> byte1;
            Svd2cppObjects::Bitfield<16, 8> byte2;
            Svd2cppObjects::Bitfield<8, 8> byte3;
            Svd2cppObjects::Bitfield<0, 8> byte4;

            register1(REG_ADDR base) : byte1{base}, byte2{base}, byte3{base}, byte4{base} {};
        };
    }
}

TEST_CASE("Basic register init")
{

    // Simulate memory
    auto arr = new std::array<REG_ADDR, 5>;
    *arr = {0, 0, 0x01020304, 0, 0};

    const size_t resetValue{0};

    using RegisterType = Svd2cppObjects::Register<0x8, Svd2cppObjects::MyRegister::register1, resetValue>;

    auto addr = reinterpret_cast<REG_ADDR>(&arr->at(0));
    auto reg = RegisterType{addr};

    for (size_t i = 0; i < arr->size(); i++)
    {
        std::cout << "Addr: " << static_cast<void*>(&(*arr)[i]) << " Value: " << std::hex << static_cast<int>((*arr)[i])
                  << "\n";
    }

    std::cout << "Addr" << static_cast<void*>(&reg) << std::endl;
    std::cout << "Addr" << static_cast<void*>(&reg->byte1) << std::endl;
    std::cout << "Addr" << reg->byte1.internalAddress() << std::endl;

    CHECK(reg->byte1.get() == 0x1);
    CHECK(reg->byte2.get() == 0x2);
    CHECK(reg->byte3.get() == 0x3);
    CHECK(reg->byte4.get() == 0x4);

    CHECK(reg->byte1.internalValue() == arr->at(2));
    CHECK(reg->byte2.internalValue() == arr->at(2));
    CHECK(reg->byte3.internalValue() == arr->at(2));
    CHECK(reg->byte4.internalValue() == arr->at(2));

    CHECK(reg->byte1.internalAddress() == &arr->at(2));
    CHECK(reg->byte2.internalAddress() == &arr->at(2));
    CHECK(reg->byte3.internalAddress() == &arr->at(2));
    CHECK(reg->byte4.internalAddress() == &arr->at(2));

    for (size_t i = 0; i < arr->size(); i++)
    {
        std::cout << "Addr: " << static_cast<void*>(&(*arr)[i]) << " Value: " << std::hex << static_cast<int>((*arr)[i])
                  << "\n";
    }
}

TEST_CASE("Basic getter setter")
{

    // Simulate memory
    auto arr = new std::array<REG_ADDR, 5>;
    *arr = {0, 0, 0, 0, 0};

    const size_t offset{0};
    const size_t resetValue{0};

    auto addr = reinterpret_cast<REG_ADDR>(&arr->at(2));
    auto reg = Svd2cppObjects::Register<offset, Svd2cppObjects::MyRegister::register1, resetValue>{addr};

    reg->byte1 = 0x1;
    reg->byte2 = 0xFF;
    reg->byte3 = 0x0A;
    reg->byte4 = 0x05;

    CHECK(reg->byte1 == 0x1);
    CHECK(reg->byte2 == 0xFF);
    CHECK(reg->byte3 == 0x0A);
    CHECK(reg->byte4 == 0x05);

    for (size_t i = 0; i < arr->size(); i++)
    {
        std::cout << "Addr: " << static_cast<void*>(&(*arr)[i]) << " Value: " << std::hex << static_cast<int>((*arr)[i])
                  << "\n";
    }
}

TEST_CASE("reset")
{

    // Simulate memory
    auto arr = new std::array<REG_ADDR, 5>;
    *arr = {0, 0, 0, 0, 0};

    const size_t offset{0};
    const size_t resetValue{0};

    auto addr = reinterpret_cast<REG_ADDR>(&arr->at(2));
    auto reg = Svd2cppObjects::Register<offset, Svd2cppObjects::MyRegister::register1, resetValue>{addr};

    reg->byte1 = 0x1;
    reg->byte2 = 0xFF;
    reg->byte3 = 0x0A;
    reg->byte4 = 0x05;

    reg.reset();

    CHECK(reg->byte1 == 0x0);
    CHECK(reg->byte2 == 0x0);
    CHECK(reg->byte3 == 0x0);
    CHECK(reg->byte4 == 0x0);

    for (size_t i = 0; i < arr->size(); i++)
    {
        std::cout << "Addr: " << static_cast<void*>(&(*arr)[i]) << " Value: " << std::hex << static_cast<int>((*arr)[i])
                  << "\n";
    }
}
