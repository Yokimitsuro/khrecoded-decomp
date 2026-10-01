#ifndef GX_STATE_INTERNAL_H
#define GX_STATE_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef struct GXVRamState {
    u16 lcdc;
    u16 bg;
    u16 obj;
    u16 arm7;
    u16 tex;
    u16 texPltt;
    u16 clearImage;
    u16 bgExtPltt;
    u16 objExtPltt;
    u16 subBG;
    u16 subOBJ;
    u16 subBGExtPltt;
    u16 subOBJExtPltt;
} GXVRamState;

typedef struct GXState {
    GXVRamState vram;
} GXState;

extern GXState gGXState;

#endif
