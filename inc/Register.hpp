#ifndef _REGISTER_INCLUDE_HPP_
#define _REGISTER_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Bitfield.hpp"
#include "Types.hpp"

namespace
{
// clang-format off
    #if defined(DEV_DEBUG)
    #define REGISTER_MESSAGE(message) std::cout << "  Register " << message
    #else
    #define REGISTER_MESSAGE(message)    do {} while (0)
    #endif
    // clang-format on
}

namespace Svd2cppObjects
{

    template<REG_ADDR offset, typename content, REG_ADDR resetValue>
    class Register
    {
    public:
        Register() = delete;

        explicit Register(REG_ADDR addr) : value{addr + offset}, ptr{reinterpret_cast<IO*>(addr + offset)}
        {
            REGISTER_MESSAGE("Address: 0x" << std::hex << addr + offset << " constructor\n");
        };

        ~Register()
        {
            REGISTER_MESSAGE("destructor\n");
        };

        void reset()
        {
            *ptr = resetValue;
        }

        explicit operator content*()
        {
            REGISTER_MESSAGE("explicit user defined conversion to pointer\n");
            return &value;
        }

        content* operator->()
        {
            REGISTER_MESSAGE("pointer access operator\n");
            return &value;
        }

    private:
        content value;
        IO* ptr;
    };

}  // namespace Svd2cppObjects

#endif  // _REGISTER_INCLUDE_HPP_
