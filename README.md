# Svd2cppObjects

## Introduction

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

4. In your project file where you need this library include it for example

```
#include "RCC.hpp"

```

5. Use the driver in your code

```
auto rcc = RCC { 0 };
rcc->reset()

```

6. Declare bitwitdh in root project

```
cmake -DSYSTEM_BIT_WIDTH=<SYSTEM_32_BIT|SYSTEM_64_BIT> ..

```
