#ifndef NITRO_MTX_TYPES_INTERNAL_H
#define NITRO_MTX_TYPES_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef int fx32;

typedef struct MtxFx22 {
    fx32 _00;
    fx32 _01;
    fx32 _10;
    fx32 _11;
} MtxFx22;

typedef long long fx64c;

typedef union MtxFx44 {
    struct {
        fx32 _00, _01, _02, _03;
        fx32 _10, _11, _12, _13;
        fx32 _20, _21, _22, _23;
        fx32 _30, _31, _32, _33;
    } elements;
    fx32 m[4][4];
} MtxFx44;

#endif
