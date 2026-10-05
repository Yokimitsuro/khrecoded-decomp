#ifndef NNSYS_GFD_H
#define NNSYS_GFD_H

#include "nitro/types.h"

typedef u32 NNSGfdTexKey;
typedef u32 NNSGfdPlttKey;
typedef NNSGfdTexKey (*NNSGfdFuncAllocTexVram)(u32 size, BOOL is4x4, u32 option);
typedef int (*NNSGfdFuncFreeTexVram)(NNSGfdTexKey key);

typedef struct NNSGfdFrmTexVramState {
    u32 address[10];
} NNSGfdFrmTexVramState;

#endif
