#ifndef __SVD2CPPOBJECT_TYPES_H__
#define __SVD2CPPOBJECT_TYPES_H__

#include <cstdint>

#ifndef SYSTEM_BIT_WIDTH
#if __GNUC__
#if __x86_64__ || __ppc64__
#define SYSTEM_BIT_WIDTH SYSTEM_64_BIT
#else
#define SYSTEM_BIT_WIDTH SYSTEM_32_BIT
#endif
#endif
#endif

#if (SYSTEM_BIT_WIDTH == SYSTEM_32_BIT)
using REG_ADDR = uint32_t;
using IO = volatile REG_ADDR;
#elif (SYSTEM_BIT_WIDTH == SYSTEM_64_BIT)
using REG_ADDR = uint64_t;
using IO = volatile REG_ADDR;
#endif  //

#endif  // __SVD2CPPOBJECT_TYPES_H__
