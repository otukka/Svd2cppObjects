#ifndef __SVD2CPPOBJECT_TYPES_H__
#define __SVD2CPPOBJECT_TYPES_H__

#include <cstdint>

#ifdef SYSTEM_32_BIT
using REG_ADDR = uint32_t;
using IO = volatile REG_ADDR;
#else
using REG_ADDR = uint64_t;
using IO = volatile REG_ADDR;
#endif  // DEBUG
#endif  // __SVD2CPPOBJECT_TYPES_H__