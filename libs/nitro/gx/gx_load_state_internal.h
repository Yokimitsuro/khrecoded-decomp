#ifndef GX_LOAD_STATE_INTERNAL_H
#define GX_LOAD_STATE_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef int GXVRamBGExtPltt;
typedef int GXVRamOBJExtPltt;
typedef int GXVRamTex;
typedef int GXVRamTexPltt;

typedef struct GXExtPlttLoadState {
    u32 subBGExtPltt;
    u32 objExtPlttLCDCBase;
    GXVRamOBJExtPltt objExtPltt;
    u32 bgExtPlttLCDCOffset;
    u32 bgExtPlttLCDCBase;
    GXVRamBGExtPltt bgExtPltt;
    u32 subOBJExtPltt;
} GXExtPlttLoadState;

typedef struct GXTextureLoadState {
    u32 reserved0;
    u32 texLCDCBase1;
    u32 texPlttLCDCBase;
    GXVRamTexPltt texPltt;
    u32 reserved10;
    GXVRamTex tex;
    u32 texLCDCBase2;
    u32 texBlock1Size;
} GXTextureLoadState;

extern GXExtPlttLoadState gGXExtPlttLoadState;
extern GXTextureLoadState gGXTextureLoadState;

#endif
