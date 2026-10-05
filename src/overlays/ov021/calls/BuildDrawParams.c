#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x2c];
    u32 colorR;
    u32 colorG;
    u32 colorB;
    u32 alpha;
    VecFx32 scale;
    u8 pad_4c[0x11];
    u8 layer : 4;
    u8 unk_5d : 4;
} ModelDesc;

typedef struct {
    u8 flags;
    u8 pad_01[7];
    u32 transform[4];
    u8 pad_18[0x120];
    ModelDesc *desc;
} ModelObject;

typedef struct {
    u32 transform[4];
    u8 colorR;
    u8 colorG;
    u8 colorB;
    u8 pad_13;
    VecFx32 scale;
    u32 alpha;
    u16 flags;
    u8 layer;
    u8 pad_27;
} DrawParams;

extern void *GetBoundedEntryField(int index);
extern void ZeroBytes0x28(DrawParams *params);

void BuildDrawParams(ModelObject *object, int index, DrawParams *params) {
    ModelDesc *desc = object->desc;
    GetBoundedEntryField(index);
    ZeroBytes0x28(params);
    params->transform[0] = object->transform[0];
    params->transform[1] = object->transform[1];
    params->transform[2] = object->transform[2];
    params->transform[3] = object->transform[3];
    params->colorR = desc->colorR;
    params->colorG = desc->colorG;
    params->colorB = desc->colorB;
    if (object->flags & 1) {
        params->flags = (params->flags & ~1) | 1;
    }
    if (object->flags & 2) {
        params->flags |= 0x80;
    }
    if (object->flags & 4) {
        params->flags |= 0x10;
    }
    params->scale = desc->scale;
    params->alpha = desc->alpha;
    if (desc->flags & 6) {
        params->flags |= 8;
    }
    if (desc->flags & 0x1000) {
        params->flags |= 0x400;
    }
    params->layer = desc->layer;
    if (desc->flags & 0x800) {
        params->flags |= 0x100;
    }
    if (desc->flags & 0x4000) {
        params->flags |= 0x1000;
    }
}
