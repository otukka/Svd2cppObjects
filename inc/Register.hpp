#ifndef _REGISTER_INCLUDE_HPP_
#define _REGISTER_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Property.hpp"
#include "Types.hpp"

template<size_t offset, typename content>
class Register
{
    content value;

public:
    Register() = delete;
    explicit Register(REG_ADDR addr) : value{addr + offset} {};
    ~Register(){};

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