#include <catch2/catch_all.hpp>

#include "Bitfield.hpp"
namespace
{
    using namespace Svd2cppObjects;
}
#define INIT_BITS(offset, width)                                                                                       \
    REG_ADDR* p = new REG_ADDR;                                                                                        \
    *p = 0;                                                                                                            \
    auto base = reinterpret_cast<REG_ADDR>(p);                                                                         \
    auto bits = Bitfield<offset, width>{base};

TEST_CASE("Init 32-bits")
{
    // Init empty
    {
        INIT_BITS(0, 32);
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0);
    }

    // Init zero
    {
        INIT_BITS(0, 32);
        bits = 0;
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0);
    }

    // Init one
    {
        INIT_BITS(0, 32);
        bits = 1;
        CHECK(bits->get() == 1);
        CHECK(bits->internalValue() == 1);
    }

    // Init nearly full
    {
        INIT_BITS(0, 32);
        bits = 0x7FFFFFFF;
        CHECK(bits->get() == 0x7FFFFFFF);
        CHECK(bits->internalValue() == 0x7FFFFFFF);
    }

    // Init full
    {
        INIT_BITS(0, 32);
        bits = 0xFFFFFFFF;
        CHECK(bits->get() == 0xFFFFFFFF);
        CHECK(bits->internalValue() == 0xFFFFFFFF);
    }

    // Init with random value
    {
        INIT_BITS(0, 32);
        bits = 4321;
        CHECK(bits->get() == 4321);
        CHECK(bits->internalValue() == 4321);
    }
}

TEST_CASE("Init 4-bits")
{
    // Init with full value zero offset
    {
        INIT_BITS(0, 4);
        bits = 0xF;
        CHECK(bits->get() == 0xF);
        CHECK(bits->internalValue() == 0xF);
    }

    // Init with one value half-byte offset
    {
        INIT_BITS(4, 4);
        bits->set(0x1);
        CHECK(bits->get() == 0x1);
        CHECK(bits->internalValue() == 0x10);
    }
    // Init with full value half-byte offset
    {
        INIT_BITS(4, 4);
        bits->set(0xF);
        CHECK(bits->get() == 0xF);
        CHECK(bits->internalValue() == 0xF0);
    }
}

TEST_CASE("Init 8-bits")
{

    // Init with value and offset 1
    {
        INIT_BITS(1, 3);
        bits = 0x7;
        CHECK(bits->get() == 0x7);
    }

    // Init with value and offset 2
    {
        INIT_BITS(2, 2);
        bits = 0x3;
        CHECK(bits->get() == 0x3);
    }

    // Init byte width
    {
        INIT_BITS(0, 8);
        bits = 0xA5;
        CHECK(bits->get() == 0xA5);
        CHECK(bits->internalValue() == 0xA5);
    }
}

TEST_CASE("Set")
{
    // Set zero
    {
        INIT_BITS(0, 32);
        bits = 1;
        bits->set(0);
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0);
    }
    // Set one
    {
        INIT_BITS(0, 32);
        bits->set(1);
        CHECK(bits->get() == 1);
        CHECK(bits->internalValue() == 1);
    }

    // Set larger
    {
        INIT_BITS(0, 32);
        bits->set(1234);
        CHECK(bits->get() == 1234);
    }

    // Set one with offset
    {
        INIT_BITS(0, 1);
        bits->set(1);
        CHECK(bits->get() == 1);
        CHECK(bits->internalValue() == 1);
    }

    // Set one with offset
    {
        INIT_BITS(1, 1);
        bits->set(1);
        CHECK(bits->get() == 1);
        CHECK(bits->internalValue() == 2);
    }

    // Set one with offset
    {
        INIT_BITS(2, 1);
        bits->set(1);
        CHECK(bits->get() == 1);
        CHECK(bits->internalValue() == 4);
    }

    // Set()
    {
        INIT_BITS(0, 32);
        bits->set();
        CHECK(bits->get() == 0xFFFFFFFF);
        CHECK(bits->internalValue() == 0xFFFFFFFF);
    }
}

TEST_CASE("Set with overflowing value")
{
    // 2-bits zero offset
    {
        INIT_BITS(0, 2);
        bits->set(5);
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0);
    }

    // 2-bits 24-bit offset
    {
        INIT_BITS(24, 2);
        bits->set(0xFF);
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0);
    }

    // 2-bits preserve original
    {
        INIT_BITS(0, 2);
        bits->set(3);
        bits->set(5);
        CHECK(bits->get() == 3);
        CHECK(bits->internalValue() == 3);
    }

    // 2-bits preserve original offset
    {
        INIT_BITS(5, 2);
        bits->set(3);
        bits->set(5);
        CHECK(bits->get() == 3);
        CHECK(bits->internalValue() == 96);
    }
}

TEST_CASE("Clear")
{
    // Clear full
    {
        INIT_BITS(0, 32);
        bits = 0xA5A5A5A5;
        CHECK(bits->get() == 0xA5A5A5A5);
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0);
    }

    // Clear empty
    {
        INIT_BITS(0, 32);
        CHECK(bits->get() == 0);
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0);
    }

    // Clear zero
    {
        INIT_BITS(0, 32);
        bits = 0;
        CHECK(bits->get() == 0);
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0);
    }

    // Clear first byte
    {
        INIT_BITS(0, 8);
        bits = 0xFF;
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0x00);
    }
    // Clear second byte
    {
        INIT_BITS(8, 8);
        bits = 0xFF;
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0x00);
    }
    // Clear third byte
    {
        INIT_BITS(16, 8);
        bits = 0xFF;
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0x00);
    }
    // Clear last byte
    {
        INIT_BITS(24, 8);
        bits = 0xFF;
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0x00);
    }

    // Clear half-byte
    {
        INIT_BITS(0, 4);
        bits = 0xF;
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0x0);
    }
    // Clear half-byte
    {
        INIT_BITS(4, 4);
        bits = 0xF;
        bits->clear();
        CHECK(bits->get() == 0);
        CHECK(bits->internalValue() == 0x0);
    }
}

TEST_CASE("Merge")
{
    // Merge to empty
    {
        INIT_BITS(0, 32);
        bits->merge(0x50A0);
        CHECK(bits->get() == 0x50A0);
        CHECK(bits->internalValue() == 0x50A0);
    }
    // Merge empty to empty
    {
        INIT_BITS(0, 32);
        bits->merge(0x0);
        CHECK(bits->get() == 0x0);
        CHECK(bits->internalValue() == 0x0);
    }

    // Merge As and 5s
    {
        INIT_BITS(0, 32);
        bits = 0xA050;
        bits->merge(0x50A0);
        CHECK(bits->get() == 0xF0F0);
        CHECK(bits->internalValue() == 0xF0F0);
    }

    // Merge half-byte
    {
        INIT_BITS(0, 4);
        bits->merge(0xA);
        CHECK(bits->get() == 0xA);
        CHECK(bits->internalValue() == 0x0A);
    }

    // Merge half-byte
    {
        INIT_BITS(4, 4);
        bits->merge(0xA);
        CHECK(bits->get() == 0xA);
        CHECK(bits->internalValue() == 0xA0);
    }
}

TEST_CASE("Flip")
{
    // 10101010
    {
        INIT_BITS(0, 32);
        bits = 0xAAAAAAAA;
        bits->flip();
        CHECK(bits->get() == 0x55555555);
        CHECK(bits->internalValue() == 0x55555555);
    }

    // Flip first byte
    {
        INIT_BITS(0, 8);
        bits = 0xAA;
        bits->flip();
        CHECK(bits->get() == 0x55);
        CHECK(bits->internalValue() == 0x00000055);
    }
    // Flip second byte
    {
        INIT_BITS(8, 8);
        bits = 0xAA;
        bits->flip();
        CHECK(bits->get() == 0x55);
        CHECK(bits->internalValue() == 0x00005500);
    }
    // Flip third byte
    {
        INIT_BITS(16, 8);
        bits = 0xAA;
        bits->flip();
        CHECK(bits->get() == 0x55);
        CHECK(bits->internalValue() == 0x00550000);
    }
    // Flip last byte
    {
        INIT_BITS(24, 8);
        bits = 0xAA;
        bits->flip();
        CHECK(bits->get() == 0x55);
        CHECK(bits->internalValue() == 0x55000000);
    }
}
