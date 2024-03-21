#ifndef _PERIPHERAL_INCLUDE_HPP_
#define _PERIPHERAL_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Register.hpp"
#include "Types.hpp"

namespace Svd2cppObjects
{

    class PeripheralBase
    {
    };

    template<REG_ADDR offset, typename content>
    class Peripheral : public PeripheralBase
    {
    public:
        content value;

        Peripheral() = delete;
        explicit Peripheral(REG_ADDR addr) : value{addr + offset}
        {
#if defined(DEV_DEBUG)
            std::cout << "Peripheral: constructor, Address: 0x" << std::hex << addr << ", Offset: 0x" << offset
                      << std::endl;
#endif
        };
        ~Peripheral()
        {
#if defined(DEV_DEBUG)
            std::cout << "Peripheral: destructor" << std::endl;
#endif
        };

        void* operator new(size_t n, REG_ADDR addr)
        {
            (void)n;
#if defined(DEV_DEBUG)
            std::cout << "Peripheral: new operator" << std::endl;
#endif
            return reinterpret_cast<void*>(addr + offset);
        }

        // Memory mapped IO, don't do anything here
        void operator delete(void*)
        {
#if defined(DEV_DEBUG)
            std::cout << "Peripheral: delete operator" << std::endl;
#endif
        };

        // user defined conversion to  T*
        explicit operator content*()
        {
#if defined(DEV_DEBUG)
            std::cout << "Peripheral:explicit user defined conversion to pointer" << std::endl;
#endif
            return &value;
        }

        // pointer access operator
        content* operator->()
        {
#if defined(DEV_DEBUG)
            std::cout << "Peripheral: pointer access operator" << std::endl;
#endif
            return &value;
        }
    };

}  // namespace Svd2cppObjects

#endif  // _PERIPHERAL_INCLUDE_HPP_
