
#include <catch2/catch_all.hpp>
#include <iostream>

#include "Bitfield.hpp"
#include "Peripheral.hpp"
#include "PeripheralFactory.hpp"
#include "Register.hpp"
#include "Types.hpp"

using namespace Svd2cppObjects::PLATFORM;
PeripheralFactory* PeripheralFactory::instance_ = nullptr;

TEST_CASE("Basic factory use")
{

    // Simulate memory
    auto arr = new std::array<uint8_t, 256>;
    memset(arr, 0, 256);

    auto base = reinterpret_cast<REG_ADDR>(arr);

    GROUP::PER1 object(base);

    CHECK(object->REG1->FIELD == 0x0);
    CHECK(object->REG2->FIELD == 0x0);

    object->REG1->FIELD = 0xfafafafa;

    CHECK(object->REG1->FIELD == 0xfafafafa);
    CHECK(object->REG2->FIELD == 0x0);

    auto smart_ptr = PeripheralFactory::instance()->createPER1(base);
    CHECK(smart_ptr->REG1->FIELD == 0xfafafafa);
    smart_ptr->REG1->FIELD = 0;
    CHECK(smart_ptr->REG1->FIELD == 0x0);
    CHECK(smart_ptr->REG2->FIELD == 0x0);
}
