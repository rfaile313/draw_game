#ifndef R_TYPES_H
#define R_TYPES_H

//NOTE:(Rudy) r_types is a
//typedef library just making
//some types easier to manage,
//initialize, and allocate effectively

#include <stdlib.h> //malloc, realloc, free
#include <stdint.h> //standard types
#include <limits.h> //INT32_Max, UINT32_Max
#include <string.h> //memset
#include <float.h>  //FLT_MAX

typedef uint8_t     u8;  //0..255
typedef int8_t      s8;  //-128..127
typedef uint16_t    u16; //0..65,535
typedef int16_t     s16; //-32,768..32,767
typedef uint32_t    u32; //0..4,294,967,295
typedef int32_t     s32; //-2,147,483,648..2,147,483,647
typedef uint64_t    u64; //0 .. 18,446,744,073,709,551,615
typedef int64_t     s64; //-9,223,372,036,854,775,808..9,223,372,036,854,775,807

typedef float       f32; //	-3.4E38..3.4E38
typedef double      f64; //	-1.7E308..1.7E308
typedef const char* const_str;

#define u32_max     UINT32_MAX // 4,294,967,295
#define s32_max     INT32_MAX  // 2,147,483,647
#define f32_max     FLT_MAX    // 3.4E38
#define f32_min     FLT_MIN    // -3.4E38

#endif //R_TYPES_H
