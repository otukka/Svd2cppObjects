#ifndef _REGISTER_INCLUDE_HPP_
#define _REGISTER_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Bitfield.hpp"
#include "Types.hpp"

namespace Svd2cppObjects
{

    template<REG_ADDR offset, typename content, REG_ADDR resetValue>
    class Register
    {
    public:
        content value;
        IO* ptr;

        Register() = delete;

        explicit Register(REG_ADDR addr) : value{addr + offset}, ptr{reinterpret_cast<IO*>(addr + offset)}
        {
#if defined(DEV_DEBUG)
            std::cout << "  Register: constructor" << std::endl;
#endif
        };

        ~Register()
        {
#if defined(DEV_DEBUG)
            std::cout << "  Register: destructor" << std::endl;
#endif
        };

        void reset()
        {
            *ptr = resetValue;
        }

        void* operator new(size_t n, REG_ADDR addr)
        {
            (void)n;
#if defined(DEV_DEBUG)
            std::cout << "  Register: new operator" << std::endl;
#endif
            return reinterpret_cast<void*>(addr + offset);
        }

        void operator delete(void*)
        {
#if defined(DEV_DEBUG)
            std::cout << "  Register: delete operator" << std::endl;
#endif
        };

        content* operator->()
        {
#if defined(DEV_DEBUG)
            std::cout << "  Register: pointer access operator" << std::endl;
#endif
            return &value;
        }
    };

}  // namespace Svd2cppObjects

#endif  // _REGISTER_INCLUDE_HPP_
