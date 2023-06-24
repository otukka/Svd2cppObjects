#ifndef _REGISTER_INCLUDE_HPP_
#define _REGISTER_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Property.hpp"
#include "Types.hpp"

template<size_t offset, typename content, REG_ADDR resetValue>
class Register
{
    IO* ptr;
    content value;

public:
    Register() = delete;
    explicit Register(REG_ADDR addr) : value{addr + offset}, ptr{reinterpret_cast<IO*>(addr + offset)} {};
    ~Register(){};

    void reset()
    {
        *ptr = resetValue;
    }

    void* operator new(size_t n, REG_ADDR addr)
    {
        return reinterpret_cast<void*>(addr);
    }

    void operator delete(void*){};

    content* operator->()
    {
        // std::cout << "pointer access operator" << std::endl;
        return &value;
    }
};

#endif  // _REGISTER_INCLUDE_HPP_