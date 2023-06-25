#ifndef __PERIPHERALFACTORY_H__
#define __PERIPHERALFACTORY_H__

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

    PeripheralBase* create(std::string name)
    {
        if (peripherals.find(name) != peripherals.end())
        {
            return instance_->peripherals[name];
        }
        return static_cast<PeripheralBase*>(nullptr);
    }

    void registerPeripheral(const std::string& name, PeripheralBase* peripheral)
    {
        instance()->peripherals[name] = peripheral;
        // peripherals.insert(std::make_pair<std::string, PeripheralBase*>(std::string(name), new PeripheralBase));
        // peripherals.at(name) = peripheral;
    }
};

static PeripheralFactory* instance_;

}  // namespace Svd2cppObjects

#endif  // __PERIPHERALFACTORY_H__