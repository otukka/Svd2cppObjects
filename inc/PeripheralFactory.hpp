#ifndef __PERIPHERALFACTORY_H__
#define __PERIPHERALFACTORY_H__

#include <map>
#include <string>

#include "Peripheral.hpp"
namespace Svd2cppObjects
{

class PeripheralFactory
{
private:
    static std::map<std::string, PeripheralBase*> peripherals;

public:
    PeripheralFactory() = delete;
    ~PeripheralFactory() = delete;

    static PeripheralBase* create(std::string name)
    {
        if (peripherals.find(name) != peripherals.end())
        {
            return peripherals[name];
        }
        return static_cast<PeripheralBase*>(nullptr);
    }

    static void registerPeripheral(std::string name, PeripheralBase* peripheral)
    {
        peripherals.insert(std::pair<std::string, PeripheralBase*>(name, peripheral));
    }
};

}  // namespace Svd2cppObjects

#endif  // __PERIPHERALFACTORY_H__