#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <array>
#include <cstddef>
#include <iostream>
#include <limits>

#include "Types.hpp"

namespace
{

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

    template<REG_ADDR offset, REG_ADDR width>
    class Bitfield
    {
    private:
        IO* value;

    public:
        Bitfield() = default;
        explicit Bitfield(REG_ADDR addr)
        {
            value = reinterpret_cast<REG_ADDR*>(addr);
        };
        ~Bitfield() = default;

        void* operator new(size_t n, REG_ADDR addr)
        {
            (void)n;
            return reinterpret_cast<void*>(addr);
        }

        // Memory mapped IO, don't do anything here
        void operator delete(void*){};

        IO* operator=(const REG_ADDR& f)
        {
            // std::cout << "copy assignment operator" << std::endl;
            set(f);
            return value;
        }

        IO* operator=(REG_ADDR&& f)
        {
            // std::cout << "move assignment operator" << std::endl;
            set(std::move(f));
            return value;
        }

        IO* operator()()
        {
            // std::cout << "function call operator" << std::endl;
            return get();
        }

        operator REG_ADDR()
        {
            // std::cout << "user defined conversion" << std::endl;
            return get();
        }

        explicit operator REG_ADDR*()
        {
            // std::cout << "explicit user defined conversion to pointer" << std::endl;
            return &get();
        }

        REG_ADDR* operator->()
        {
            // std::cout << "pointer access operator" << std::endl;
            return &get();
        }

        void set()
        {
            merge(ones(width));
        }

        void set(REG_ADDR newValue)
        {
            if (newValue <= ones(width))
            {
                clear();
                merge(newValue);
            }
        }

        void merge(REG_ADDR newValue)
        {
            if (newValue <= ones(width))
            {
                *value |= (newValue << offset);
            }
        }

        REG_ADDR get()
        {
            return ((*value & (ones(width) << offset)) >> offset);
        }

        void clear()
        {
            *value &= ~(ones(width) << offset);
        }

        void flip()
        {
            *value ^= (ones(width) << offset);
        }

#ifdef TEST_HELPERS
        REG_ADDR internalValue()
        {
            return *value;
        }
        IO* internalAddress()
        {
            return value;
        }
#endif  // TEST_HELPERS
    };

}  // namespace Svd2cppObjects

#endif  // __BITFIELD_H__
