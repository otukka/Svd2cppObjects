
#include <catch2/catch_all.hpp>
#include <iostream>

#include "Bitfield.hpp"
#include "Peripheral.hpp"
#include "PeripheralFactory.hpp"
#include "Register.hpp"
#include "Types.hpp"

Svd2cppObjects::PeripheralFactory* Svd2cppObjects::PeripheralFactory::instance_ = nullptr;

struct register1
{
    Svd2cppObjects::Bitfield<0, 32> word;
    register1(REG_ADDR base) : word{base} {}
};

struct peripheral1
{
    Svd2cppObjects::Register<0x16, register1, 0x0> reg1;
    Svd2cppObjects::Register<0x8, register1, 0x0> reg2;

    peripheral1(REG_ADDR base) : reg1{base}, reg2{base} {};
};

using PeripheralType = Svd2cppObjects::Peripheral<0, peripheral1>;

TEST_CASE("Basic factory use")
{

    // Simulate memory
    auto arr = new std::array<uint8_t, 256>;
    memset(arr, 0, 256);

    auto base = reinterpret_cast<REG_ADDR>(arr);
    auto stored = PeripheralType{base};

    CHECK(stored->reg1->word == 0x0);
    stored->reg1->word = 0xfafafafa;
    CHECK(stored->reg1->word == 0xfafafafa);

    const std::string peripheralName{"peripheral"};

    Svd2cppObjects::PeripheralFactory::instance()->registerPeripheral(peripheralName,
                                                                      reinterpret_cast<PeripheralType*>(&stored));

    auto fetched = *Svd2cppObjects::PeripheralFactory::instance()->create<PeripheralType>(peripheralName);

    CHECK(fetched->reg1->word == 0xfafafafa);
    fetched->reg1->word = 0xdeadbeef;
    CHECK(fetched->reg1->word == 0xdeadbeef);
}
