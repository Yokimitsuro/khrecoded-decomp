#ifndef NITRO_FX_TYPES_H
#define NITRO_FX_TYPES_H

#include "nitro/types.h"

#define FX32_SHIFT 12
#define FX32_ONE 0x1000

typedef s64 fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

#endif
