#ifndef _SVD_2_CPP_OBJECTS_PERIPHERAL_FACTORY_INCLUDE_HPP_
#define _SVD_2_CPP_OBJECTS_PERIPHERAL_FACTORY_INCLUDE_HPP_

#include <memory>

#include "Bitfield.hpp"
#include "Peripheral.hpp"
#include "Register.hpp"

namespace Svd2cppObjects
{
    namespace PLATFORM
    {

        namespace GROUP
        {
            struct REG1_
            {
                Bitfield<0, 32> FIELD;
                REG1_(REG_ADDR base) : FIELD{base} {}
            };

            struct REG2_
            {
                Bitfield<0, 32> FIELD;
                REG2_(REG_ADDR base) : FIELD{base} {}
            };

            struct PER1_
            {
                Register<0x0, REG1_, 0x0> REG1;
                Register<0x4, REG2_, 0x0> REG2;

                PER1_(REG_ADDR base) : REG1{base}, REG2{base} {};
            };

            using PER1 = Peripheral<0, PER1_>;
        }  // namespace GROUP

        class PeripheralFactory
        {
        private:
            static PeripheralFactory* instance_;

            PeripheralFactory(){};
            ~PeripheralFactory(){};

        public:
            PeripheralFactory(PeripheralFactory& other) = delete;
            void operator=(const PeripheralFactory&) = delete;

            static PeripheralFactory* instance()
            {
                if (instance_ == nullptr)
                {
                    instance_ = new PeripheralFactory();
                }
                return instance_;
            }

            std::shared_ptr<GROUP::PER1_> createPER1(REG_ADDR base)
            {
                return std::make_shared<GROUP::PER1_>(base);
            }
        };

    }  // namespace PLATFORM
}  // namespace Svd2cppObjects

#endif  // _SVD_2_CPP_OBJECTS_PERIPHERAL_FACTORY_INCLUDE_HPP_
