#ifndef _PERIPHERAL_INCLUDE_HPP_
#define _PERIPHERAL_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Types.hpp"

template<size_t offset, typename content>
class Peripheral
{

    content value;

public:
    Peripheral() = delete;
    explicit Peripheral(REG_ADDR addr) : value{addr + offset} {};
    ~Peripheral(){};

    void* operator new(size_t n, REG_ADDR addr)
    {
        return reinterpret_cast<void*>(addr);
    }

    // Memory mapped IO, don't do anything here
    void operator delete(void*){};

    // pointer access operator
    content* operator->()
    {
        // std::cout << "pointer access operator" << std::endl;
        return &value;
    }
};

#endif  // _PERIPHERAL_INCLUDE_HPP_