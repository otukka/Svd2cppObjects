#ifndef _SVD_2_CPP_OBJECTS_PERIPHERAL_FACTORY_INCLUDE_HPP_
#define _SVD_2_CPP_OBJECTS_PERIPHERAL_FACTORY_INCLUDE_HPP_

#include <string>
#include <unordered_map>

#include "Peripheral.hpp"
namespace Svd2cppObjects
{

class PeripheralFactory
{
private:
    static PeripheralFactory* instance_;
    std::unordered_map<std::string, PeripheralBase*> peripherals;

    PeripheralFactory(){};
    ~PeripheralFactory(){};

public:
    static PeripheralFactory* instance()
    {
        if (instance_ == nullptr)
        {
            instance_ = new PeripheralFactory();
        }
        return instance_;
    }

    template<typename T>
    T* create(std::string name)
    {
        if (peripherals.find(name) != peripherals.end())
        {
            return reinterpret_cast<T*>(instance()->peripherals[name]);
        }
        return static_cast<T*>(nullptr);
    }

    void registerPeripheral(const std::string& name, PeripheralBase* peripheral)
    {
        instance()->peripherals[name] = peripheral;
    }
};

}  // namespace Svd2cppObjects

#endif  // _SVD_2_CPP_OBJECTS_PERIPHERAL_FACTORY_INCLUDE_HPP_