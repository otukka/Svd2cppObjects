
#include <catch2/catch_all.hpp>
#include <iostream>

#include "Bitfield.hpp"
#include "Register.hpp"
#include "Types.hpp"
#include "utilities.hpp"

namespace
{
    using namespace Svd2cppObjects;
}

namespace Svd2cppObjects
{
    namespace MyRegister
    {

        struct register1
        {
            Bitfield<24, 8> byte1;
            Bitfield<16, 8> byte2;
            Bitfield<8, 8> byte3;
            Bitfield<0, 8> byte4;

            register1(REG_ADDR base) : byte1{base}, byte2{base}, byte3{base}, byte4{base} {};
        };
    }
}

TEST_CASE("Basic register init")
{

    auto arr = memoryMock<REG_ADDR, 8>();

    arr->at(1) = 0x04030201;

    const size_t offset{0x04};
    const size_t resetValue{0x00};

    using RegisterType = Register<offset, MyRegister::register1, resetValue>;

    auto addr = reinterpret_cast<REG_ADDR>(&arr->at(0));
    auto reg = RegisterType{addr};

    printMemoryMock(*arr);

    CHECK(reg->byte1.get() == 0x4);
    CHECK(reg->byte2.get() == 0x3);
    CHECK(reg->byte3.get() == 0x2);
    CHECK(reg->byte4.get() == 0x1);

    CHECK(reg->byte1.internalValue() == *reinterpret_cast<REG_ADDR*>(&arr->at(1)));
    CHECK(reg->byte2.internalValue() == *reinterpret_cast<REG_ADDR*>(&arr->at(1)));
    CHECK(reg->byte3.internalValue() == *reinterpret_cast<REG_ADDR*>(&arr->at(1)));
    CHECK(reg->byte4.internalValue() == *reinterpret_cast<REG_ADDR*>(&arr->at(1)));

    CHECK(reg->byte1.internalAddress() == reinterpret_cast<REG_ADDR*>(&arr->at(1)));
    CHECK(reg->byte2.internalAddress() == reinterpret_cast<REG_ADDR*>(&arr->at(1)));
    CHECK(reg->byte3.internalAddress() == reinterpret_cast<REG_ADDR*>(&arr->at(1)));
    CHECK(reg->byte4.internalAddress() == reinterpret_cast<REG_ADDR*>(&arr->at(1)));

    printMemoryMock(*arr);
}

TEST_CASE("Basic getter setter")
{

    auto arr = memoryMock<REG_ADDR, 8>();

    const size_t offset{0};
    const size_t resetValue{0};

    auto addr = reinterpret_cast<REG_ADDR>(&arr->at(2));
    auto reg = Register<offset, MyRegister::register1, resetValue>{addr};

    reg->byte1 = 0x1;
    reg->byte2 = 0xFF;
    reg->byte3 = 0x0A;
    reg->byte4 = 0x05;

    CHECK(reg->byte1 == 0x1);
    CHECK(reg->byte2 == 0xFF);
    CHECK(reg->byte3 == 0x0A);
    CHECK(reg->byte4 == 0x05);

    printMemoryMock(*arr);
}

TEST_CASE("reset")
{

    auto arr = memoryMock<REG_ADDR, 8>();

    const size_t offset{0};
    const size_t resetValue{0xDEADBEEF};

    auto addr = reinterpret_cast<REG_ADDR>(&arr->at(0x04));
    auto reg = Register<offset, MyRegister::register1, resetValue>{addr};

    reg->byte1 = 0x01;
    reg->byte2 = 0xFF;
    reg->byte3 = 0x0A;
    reg->byte4 = 0x05;

    reg.reset();

    CHECK(reg->byte1 == 0xDE);
    CHECK(reg->byte2 == 0xAD);
    CHECK(reg->byte3 == 0xBE);
    CHECK(reg->byte4 == 0xEF);

    printMemoryMock(*arr);
}
