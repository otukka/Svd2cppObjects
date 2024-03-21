
#include <catch2/catch_all.hpp>
#include <iostream>

#include "Bitfield.hpp"
#include "Peripheral.hpp"
#include "Register.hpp"
#include "Types.hpp"

namespace
{
    using namespace Svd2cppObjects;

    struct register1
    {
        Bitfield<24, 8> byte1;
        Bitfield<16, 8> byte2;
        Bitfield<8, 8> byte3;
        Bitfield<0, 8> byte4;

        register1(REG_ADDR base) : byte1{base}, byte2{base}, byte3{base}, byte4{base} {}
    };

    struct peripheral1
    {
        Register<0x28, register1, 0x0> reg1;
        Register<0x8, register1, 0x0> reg2;

        peripheral1(REG_ADDR base) : reg1{base}, reg2{base} {};
    };

    using PeripheralType = Peripheral<0, peripheral1>;
}

TEST_CASE("Basic peripheral init")
{

    // Simulate memory
    auto arr = new std::array<uint8_t, 256>;
    memset(arr, 0, 256);

    auto base = reinterpret_cast<REG_ADDR>(arr);
    auto periph = PeripheralType{base};

    periph->reg1->byte1.set(0xA5);

    CHECK(periph->reg1->byte1 == 0xA5);
    CHECK(periph->reg1->byte2 == 0x0);
    CHECK(periph->reg1->byte3 == 0x0);
    CHECK(periph->reg1->byte4 == 0x0);

    CHECK(periph->reg2->byte1 == 0x0);
    CHECK(periph->reg2->byte2 == 0x0);
    CHECK(periph->reg2->byte3 == 0x0);
    CHECK(periph->reg2->byte4 == 0x0);

    for (size_t i = 0; i < arr->size(); i++)
    {
        std::cout << "Addr: " << static_cast<void*>(&(*arr)[i]) << " Value: " << std::hex << static_cast<int>((*arr)[i])
                  << "\n";
    }
}

TEST_CASE("Smart pointer peripheral using Peripheral class")
{

    // Simulate memory
    auto arr = new std::array<uint8_t, 256>;
    memset(arr, 0, 256);

    auto base = reinterpret_cast<REG_ADDR>(arr);
    auto periph = std::make_shared<PeripheralType>(base);

    periph->value.reg1->byte1.set(0xA5);

    CHECK(periph->value.reg1->byte1 == 0xA5);
    CHECK(periph->value.reg1->byte2 == 0x0);
    CHECK(periph->value.reg1->byte3 == 0x0);
    CHECK(periph->value.reg1->byte4 == 0x0);

    CHECK(periph->value.reg2->byte1 == 0x0);
    CHECK(periph->value.reg2->byte2 == 0x0);
    CHECK(periph->value.reg2->byte3 == 0x0);
    CHECK(periph->value.reg2->byte4 == 0x0);

    for (size_t i = 0; i < arr->size(); i++)
    {
        std::cout << "Addr: " << static_cast<void*>(&(*arr)[i]) << " Value: " << std::hex << static_cast<int>((*arr)[i])
                  << "\n";
    }
}

TEST_CASE("Smart pointer peripheral using peripheral struct")
{

    // Simulate memory
    auto arr = new std::array<uint8_t, 256>;
    memset(arr, 0, 256);

    auto base = reinterpret_cast<REG_ADDR>(arr);
    auto periph = std::make_shared<peripheral1>(base);

    periph->reg1->byte1.set(0xA5);

    CHECK(periph->reg1->byte1 == 0xA5);
    CHECK(periph->reg1->byte2 == 0x0);
    CHECK(periph->reg1->byte3 == 0x0);
    CHECK(periph->reg1->byte4 == 0x0);

    CHECK(periph->reg2->byte1 == 0x0);
    CHECK(periph->reg2->byte2 == 0x0);
    CHECK(periph->reg2->byte3 == 0x0);
    CHECK(periph->reg2->byte4 == 0x0);

    for (size_t i = 0; i < arr->size(); i++)
    {
        std::cout << "Addr: " << static_cast<void*>(&(*arr)[i]) << " Value: " << std::hex << static_cast<int>((*arr)[i])
                  << "\n";
    }
}
