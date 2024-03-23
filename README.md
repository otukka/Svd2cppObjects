# Svd2cppObjects

## Introduction

Svd2cppObjects is tool for converting System View Description (SVD) files to C++ driver library. Intention is to access memory mapped IO with C++. 

This project provides Peripheral, Register, and Bitfield classes. These classes are used to encapsulate memory addresses in a safe way. There is no more need for raw pointer handling. One could manually create driver for custom hardware with these classes.

## Requirements
Python +3.6 and virtualenv is required.

## Usage

1. Add this project as submodule to your project at root directory

```
git submodule add git@github.com:otukka/Svd2cppObjects.git
```

2. Include this project in your root `CMakeLists.txt`

```
add_subdirectory(Svd2cppObjects)
```

3. In `CMakeLists.txt` add Svd2cppObjects to some target

```
target_link_libraries(<target> PRIVATE Svd2cppObjects)
```

4. Declare bitwidth in root project

```
cmake -DSYSTEM_BIT_WIDTH=<SYSTEM_32_BIT|SYSTEM_64_BIT> ..
```

5. In your project main file include target

```
#include "<target>.hpp"
```

6. Example how to use RCC in STM32F2 platform

```
auto RCC = PeripheralFactory::instance()->createRCC();
RCC->AHB1ENR.reset();
RCC->AHB1ENR->GPIOGEN->set(1);
```

Example project can be found [here](https://github.com/otukka/Svd2cppObjects-example).
