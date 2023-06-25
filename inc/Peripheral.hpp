#ifndef _PERIPHERAL_INCLUDE_HPP_
#define _PERIPHERAL_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Types.hpp"
namespace Svd2cppObjects
{

class PeripheralBase
{
};

template<REG_ADDR offset, typename content>
class Peripheral : public PeripheralBase
{

    content value;

public:
    Peripheral() = delete;
    explicit Peripheral(REG_ADDR addr) : value{addr + offset} {};
    ~Peripheral(){};

    void* operator new(size_t n, REG_ADDR addr)
    {
        (void*)n;
        return reinterpret_cast<void*>(addr + offset);
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

}  // namespace Svd2cppObjects

#endif  // _PERIPHERAL_INCLUDE_HPP_