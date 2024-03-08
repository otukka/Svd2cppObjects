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
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: constructor" << std::endl;
#endif
            value = reinterpret_cast<REG_ADDR*>(addr);
        };
        ~Bitfield()
        {
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: destructor" << std::endl;
#endif
        };

        void* operator new(size_t n, REG_ADDR addr)
        {
            (void)n;
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: new operator" << std::endl;
#endif
            return reinterpret_cast<void*>(addr);
        }

        // Memory mapped IO, don't do anything here
        void operator delete(void*)
        {
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: delete operator" << std::endl;
#endif
        };

        IO* operator=(const REG_ADDR& f)
        {
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: copy assignment operator" << std::endl;
#endif
            set(f);
            return value;
        }

        IO* operator=(REG_ADDR&& f)
        {
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: move assignment operator" << std::endl;
#endif
            set(std::move(f));
            return value;
        }

        IO* operator()()
        {
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: function call operator" << std::endl;
#endif
            return get();
        }

        operator REG_ADDR()
        {
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: user defined conversion" << std::endl;
#endif
            return get();
        }

        explicit operator REG_ADDR*()
        {
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: explicit user defined conversion to pointer" << std::endl;
#endif
            return &get();
        }

        REG_ADDR* operator->()
        {
#if defined(DEV_DEBUG)
            std::cout << "    Bitfield: pointer access operator" << std::endl;
#endif
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
