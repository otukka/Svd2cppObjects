#ifndef __SVD2CPPOBJECTS_TESTS_UTILITIES_HPP_
#define __SVD2CPPOBJECTS_TESTS_UTILITIES_HPP_

#include <array>
#include <cstring>
#include <iomanip>
#include <memory>
#include <stddef.h>

template<typename T, size_t SIZE>
void printMemoryMock(const std::array<T, SIZE>& arr)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << "Addr: " << static_cast<const void*>(&arr[i]) << " Value: 0x" << std::setw(8) << std::setfill('0')
                  << std::hex << static_cast<int>(arr[i]) << "\n";
    }
}

template<typename T, std::size_t SIZE>
std::unique_ptr<std::array<T, SIZE>> memoryMock()
{
    auto arr = std::make_unique<std::array<T, SIZE>>();
    std::memset(arr.get(), 0, sizeof(std::array<T, SIZE>));
    return arr;
}

#endif  // __SVD2CPPOBJECTS_TESTS_UTILITIES_HPP_
