#ifndef R_TYPES_H
#define R_TYPES_H

#ifndef _types_c
#define _types_c

#include <stdlib.h> //malloc, realloc, free
#include <stdint.h> //standard types
#include <limits.h> //INT32_Max, UINT32_Max
#include <string.h> //memset
#include <float.h>  //FLT_MAX

typedef uint8_t     u8;
typedef int8_t      s8;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef s32         b32;
typedef uint_64_t   u64;
typedef int_64_t    s64;

typedef float       f32;
typedef double      f64;
typedef const char* const_str;

#define u32_max     UINT32_MAX
#define s32_max     INT32_MAX
#define f32_max     FLT_MAX
#define f32_min     FLT_MIN



#endif //R_TYPES_H
