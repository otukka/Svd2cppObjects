#ifndef _PERIPHERAL_INCLUDE_HPP_
#define _PERIPHERAL_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Register.hpp"
#include "Types.hpp"

namespace
{
    // clang-format off
    #if defined(DEV_DEBUG)
    #define PERIPHERAL_MESSAGE(message) std::cout << "Peripheral " << message
    #else
    #define PERIPHERAL_MESSAGE(message)    do {} while (0)
    #endif
    // clang-format on
}

namespace Svd2cppObjects
{

    class PeripheralBase
    {
    };

    template<REG_ADDR offset, typename content>
    class Peripheral : public PeripheralBase
    {
    public:
        Peripheral() = delete;
        Peripheral(const Peripheral&) = delete;
        Peripheral& operator=(const Peripheral&) = delete;
        Peripheral(Peripheral&&) = delete;
        Peripheral& operator=(Peripheral&&) = delete;

        explicit Peripheral(const REG_ADDR addr) : value{addr + offset}
        {
            PERIPHERAL_MESSAGE("Address: 0x" << std::hex << addr + offset << " constructor\n");
        };

        ~Peripheral()
        {
            PERIPHERAL_MESSAGE("destructor\n");
        }

        explicit operator content*()
        {
            PERIPHERAL_MESSAGE("explicit user defined conversion to pointer\n");
            return &value;
        }

        content* operator->()
        {
            PERIPHERAL_MESSAGE("pointer access operator\n");
            return &value;
        }

    private:
        content value;
    };
}  // namespace Svd2cppObjects

#endif  // _PERIPHERAL_INCLUDE_HPP_
