#ifndef _REGISTER_INCLUDE_HPP_
#define _REGISTER_INCLUDE_HPP_

#include <array>
#include <cstddef>
#include <iostream>

#include "Property.hpp"
#include "Types.hpp"

namespace Svd2cppObjects
{

template<REG_ADDR offset, typename content, REG_ADDR resetValue>
class Register
{
    content value;
    IO* ptr;

public:
    Register() = delete;
    explicit Register(REG_ADDR addr) : value{addr + offset}, ptr{reinterpret_cast<IO*>(addr + offset)}
    {
        std::cout << "Register init" << std::endl;
    };
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

}  // namespace Svd2cppObjects

#endif  // _REGISTER_INCLUDE_HPP_