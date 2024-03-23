
#include <catch2/catch_all.hpp>
#include <iomanip>
#include <iostream>

#include "Bitfield.hpp"
#include "Peripheral.hpp"
#include "Register.hpp"
#include "Types.hpp"
#include "utilities.hpp"

namespace
{

    using namespace Svd2cppObjects;

    const REG_ADDR reg2reset = 0xDEADBEEF;

    struct register1
    {
        Bitfield<24, 8> byte1;
        Bitfield<16, 8> byte2;
        Bitfield<8, 8> byte3;
        Bitfield<0, 8> byte4;

        register1(REG_ADDR base) : byte1{base}, byte2{base}, byte3{base}, byte4{base} {}
    };

    struct register2
    {
        Bitfield<0, 32> word;

        register2(REG_ADDR base) : word{base} {}
    };

    struct peripheral1
    {
        Register<0x00, register1, 0x01020304> reg1;
        Register<0x04, register2, reg2reset> reg2;

        peripheral1(REG_ADDR base) : reg1{base}, reg2{base} {};
    };

    using PeripheralType = Peripheral<0, peripheral1>;
}

TEST_CASE("Peripheral from struct init", "[PeripheralTests]")
{
    auto arr = memoryMock<REG_ADDR, 8>();

    auto base = reinterpret_cast<REG_ADDR>(&arr->at(3));
    std::cout << "\nSimulated memory is at address: 0x" << std::hex << base << "\n\n";
    auto periph = peripheral1(base);

    CHECK(reinterpret_cast<REG_ADDR>(periph.reg1->byte1.internalAddress()) == base);
    CHECK(reinterpret_cast<REG_ADDR>(periph.reg2->word.internalAddress()) == (base + 0x04));

    periph.reg1.reset();
    periph.reg2.reset();

    CHECK(periph.reg1->byte2 == 0x2);
    CHECK(periph.reg1->byte3 == 0x3);
    CHECK(periph.reg1->byte4 == 0x4);

    periph.reg2->word->set(0);
    CHECK(periph.reg2->word == 0x0);

    periph.reg2.reset();
    CHECK(periph.reg2->word == reg2reset);

    printMemoryMock(*arr);
}

TEST_CASE("Peripheral from Peripheral class init", "[PeripheralTests]")
{

    auto arr = memoryMock<REG_ADDR, 8>();

    auto base = reinterpret_cast<REG_ADDR>(&arr->at(3));
    std::cout << "\nSimulated memory is at address: 0x" << std::hex << base << "\n\n";
    auto periph = PeripheralType(base);

    CHECK(reinterpret_cast<REG_ADDR>(periph->reg1->byte1.internalAddress()) == base);
    CHECK(reinterpret_cast<REG_ADDR>(periph.value.reg2->word.internalAddress()) == (base + 0x04));

    // Syntax options
    periph.value.reg1.reset();
    periph->reg2.reset();

    periph->reg1->byte1->set(0x00);
    periph->reg1->byte2->set(0x01);
    periph->reg1->byte3->set(0x40);
    periph->reg1->byte4->set(0xFF);

    CHECK(periph->reg1->byte1 == 0x00);
    CHECK(periph->reg1->byte2 == 0x01);
    CHECK(periph->reg1->byte3 == 0x40);
    CHECK(periph->reg1->byte4 == 0xFF);

    CHECK(periph->reg2->word == reg2reset);

    printMemoryMock(*arr);
}

TEST_CASE("Smart pointer peripheral using Peripheral class", "[PeripheralTests]")
{

    auto arr = memoryMock<REG_ADDR, 8>();

    auto base = reinterpret_cast<REG_ADDR>(&arr->at(3));
    std::cout << "\nSimulated memory is at address: 0x" << std::hex << base << "\n\n";

    auto periph = std::make_shared<PeripheralType>(base);

    CHECK(reinterpret_cast<REG_ADDR>(periph->value.reg1->byte1.internalAddress()) == base);
    CHECK(reinterpret_cast<REG_ADDR>(periph->value.reg2->word.internalAddress()) == (base + 0x04));

    periph->value.reg1.reset();
    periph->value.reg2.reset();

    periph->value.reg1->byte1->set(0xAA);
    periph->value.reg1->byte2->set(0xBB);
    periph->value.reg1->byte3->set(0xCC);
    periph->value.reg1->byte4->set(0xDD);

    CHECK(periph->value.reg1->byte1->get() == 0xAA);
    CHECK(periph->value.reg1->byte2->get() == 0xBB);
    CHECK(periph->value.reg1->byte3->get() == 0xCC);
    CHECK(periph->value.reg1->byte4->get() == 0xDD);

    CHECK(periph->value.reg2->word == reg2reset);

    printMemoryMock(*arr);
}

TEST_CASE("Pointer constructor with Peripheral class", "[PeripheralTests]")
{

    auto arr = memoryMock<REG_ADDR, 8>();

    auto base = reinterpret_cast<REG_ADDR>(&arr->at(3));
    std::cout << "\nSimulated memory is at address: 0x" << std::hex << base << "\n\n";

    auto periph = *new PeripheralType(base);

    periph->reg2.reset();
    CHECK(periph->reg2->word == reg2reset);

    printMemoryMock(*arr);
}

TEST_CASE("Smart pointer (new) peripheral using peripheral class", "[PeripheralTests]")
{

    auto arr = memoryMock<REG_ADDR, 8>();

    auto base = reinterpret_cast<REG_ADDR>(&arr->at(3));
    std::cout << "\nSimulated memory is at address: 0x" << std::hex << base << "\n\n";

    auto periph = std::shared_ptr<PeripheralType>(new PeripheralType(base));

    periph->value.reg2.reset();
    CHECK(periph->value.reg2->word == reg2reset);

    printMemoryMock(*arr);
}

TEST_CASE("Smart pointer (make_shared) peripheral using peripheral struct", "[PeripheralTests]")
{

    auto arr = memoryMock<REG_ADDR, 8>();

    auto base = reinterpret_cast<REG_ADDR>(&arr->at(3));
    std::cout << "\nSimulated memory is at address: 0x" << std::hex << base << "\n\n";
    auto periph = std::make_shared<peripheral1>(base);

    CHECK(reinterpret_cast<REG_ADDR>(periph->reg1->byte1.internalAddress()) == base);
    CHECK(reinterpret_cast<REG_ADDR>(periph->reg2->word.internalAddress()) == (base + 0x04));

    periph->reg2.reset();

    CHECK(periph->reg2->word == reg2reset);

    printMemoryMock(*arr);
}
