#include <catch2/catch_all.hpp>
#include <iostream>

#include "Property.hpp"
#include "Types.hpp"

class MyClass
{
public:
    Svd2cppObjects::Property<REG_ADDR> prop;
    MyClass(){};
    ~MyClass(){};
};

TEST_CASE("Assingment with MyClass")
{
    {
        MyClass a{};
        const REG_ADDR b = 5;
        a.prop = b;
        CHECK(5 == a.prop);
    }
    {
        MyClass a{};
        REG_ADDR b = 5;
        a.prop = std::move(b);
        CHECK(5 == a.prop);
    }
    {
        MyClass a{};
        a.prop = 5;
        CHECK(5 == a.prop);
    }
    {
        MyClass a{};
        MyClass b{};
        a.prop = 5;
        b.prop = a.prop;
        CHECK(b.prop == a.prop);
    }
}

TEST_CASE("Function call operators")
{
    {
        MyClass a{};
        REG_ADDR* b = a.prop();
        CHECK(*b == a.prop);
    }
    {
        const MyClass a{};
        REG_ADDR b = a.prop();
        CHECK(b == a.prop);
    }
}

TEST_CASE("User defined conversions")
{
    {
        Svd2cppObjects::Property<REG_ADDR> a{};
        REG_ADDR b = a;
        CHECK(b == a);
    }
    {
        Svd2cppObjects::Property<REG_ADDR> a{};
        // REG_ADDR *b = a;  // error
    }
    {
        Svd2cppObjects::Property<REG_ADDR> a{};
        REG_ADDR* b = static_cast<REG_ADDR*>(a);
        CHECK(*b == a);
    }
}
