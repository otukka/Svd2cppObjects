#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <array>
#include <cstddef>
#include <iostream>
#include <limits>

#include "Types.hpp"
namespace
{
// clang-format off
    #if defined(DEV_DEBUG)
    #define BITFIELD_MESSAGE(message) std::cout << "    Bitfield " << message
    #else
    #define BITFIELD_MESSAGE(message)    do {} while (0)
    #endif
    // clang-format on

    constexpr auto ones(size_t width)
    {
        if ((width / 8) == sizeof(REG_ADDR))
        {
            return static_cast<REG_ADDR>(std::numeric_limits<REG_ADDR>::max());
        }
        return static_cast<REG_ADDR>(((1 << (width)) - 1));
    }
}

namespace Svd2cppObjects
{

    template<REG_ADDR shift, REG_ADDR width>
    class Bitfield
    {
    private:
        IO* value;

    public:
        Bitfield() = default;
        explicit Bitfield(REG_ADDR addr) : value(reinterpret_cast<REG_ADDR*>(addr))
        {
            BITFIELD_MESSAGE("Shift: " << shift << " Width: " << width << " constructor\n");
        };

        ~Bitfield()
        {
            BITFIELD_MESSAGE("destructor\n");
        };

        IO* operator=(const REG_ADDR& f)
        {
            BITFIELD_MESSAGE("copy assignment operator\n");
            set(f);
            return value;
        }

        IO* operator=(REG_ADDR&& f)
        {
            BITFIELD_MESSAGE("move assignment operator\n");
            set(std::move(f));
            return value;
        }

        IO* operator()()
        {
            BITFIELD_MESSAGE("function call operator\n");
            return get();
        }

        operator REG_ADDR()
        {
            BITFIELD_MESSAGE("user defined conversion\n");
            return get();
        }

        explicit operator REG_ADDR*()
        {
            BITFIELD_MESSAGE("explicit user defined conversion to pointer\n");
            return &get();
        }

        REG_ADDR* operator->()
        {
            BITFIELD_MESSAGE("pointer access operator\n");
            return &get();
        }

        void set()
        {
            merge(ones(width));
            BITFIELD_MESSAGE("set()\n");
        }

        void set(REG_ADDR newValue)
        {
            if (newValue <= ones(width))
            {
                clear();
                merge(newValue);
            }
            BITFIELD_MESSAGE("set(REG_ADDR newValue)\n");
        }

        void merge(REG_ADDR newValue)
        {
            if (newValue <= ones(width))
            {
                *value |= (newValue << shift);
            }
            BITFIELD_MESSAGE("merge(REG_ADDR newValue)\n");
        }

        REG_ADDR get()
        {
            return ((*value & (ones(width) << shift)) >> shift);
            BITFIELD_MESSAGE("get()\n");
        }

        void clear()
        {
            *value &= ~(ones(width) << shift);
            BITFIELD_MESSAGE("clear()\n");
        }

        void flip()
        {
            *value ^= (ones(width) << shift);
            BITFIELD_MESSAGE("flip()\n");
        }

#if defined(TEST_CODE)
        REG_ADDR internalValue()
        {
            return *value;
        }
        IO* internalAddress()
        {
            return value;
        }
#endif  // TEST_CODE
    };

}  // namespace Svd2cppObjects

#endif  // __BITFIELD_H__
