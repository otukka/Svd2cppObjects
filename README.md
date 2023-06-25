# Svd2cppObjects

> NOTE!: Currently, this is untested proof-of-concept library. Do not use.

## Introduction

TBD

## How To Use

This driver can be included in your project in few simple steps.

1. Add this project as submodule to your root project

```
git submodule add git@github.com:otukka/Svd2cppObjects.git
```

2. Include this project in your root `CMakeLists.txt`

```
add_subdirectory(Svd2cppObjects)
```

3. Add Svd2cppObjects to target

```
target_link_libraries(<target> PRIVATE Svd2cppObjects)

```

4. In your project main file iclude PeripheralFactory

```
#include "PeripheralFactory.hpp"

```

5. Initialize peripheral objects in your main function

```
Svd2cppObjects::<target-platform>::registerPeripherals();

```

6. Example how to use RCC in stm32 platform

```
auto rcc = *Svd2cppObjects::PeripheralFactory::instance()->create<RNGperipheral::RNGperipheral>(RCCname);
rcc->reset()
```

7. Declare bitwitdh in root project

```
cmake -DSYSTEM_BIT_WIDTH=<SYSTEM_32_BIT|SYSTEM_64_BIT> ..

```
