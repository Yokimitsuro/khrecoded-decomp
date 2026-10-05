#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    u32 scale;
} ModelScaleInfo;

typedef struct {
    u8 pad_00[0x20];
    u8 transform[0xf0];
    void *matrix;
} AttachedModel;

typedef struct {
    u32 flags;
    u32 pad_04;
    u16 drawFlags;
    u8 pad_0a[0x1e];
    u8 transform[4];
    ModelScaleInfo *scaleInfo;
    u8 pad_30[0xd4];
    u16 colorScale;
    u8 pad_106[0xa];
    void *matrix;
    u8 pad_114[0x114];
    AttachedModel *attached;
} DrawnModel;

extern void NNS_G3dGeBufferOP_N(int command, const void *data, int words);
extern void NNS_G3dGlbFlushP(void);
extern void func_01fff67c(u16 scale);
extern void func_01ffe1bc(void *transform);

void DrawModelWithAttachment(DrawnModel *model)
{
    u32 scale[3];
    AttachedModel *attached;
    u32 value;

    if ((model->flags & 1) && (model->flags & 2)) {
        value = model->scaleInfo->scale;
        scale[0] = value;
        scale[1] = value;
        scale[2] = value;
        NNS_G3dGeBufferOP_N(0x1b, scale, 3);
        NNS_G3dGlbFlushP();
        if (model->drawFlags & 0x40) {
            func_01fff67c(model->colorScale);
        }
        NNS_G3dGeBufferOP_N(0x17, model->matrix, 0xc);
        func_01ffe1bc(model->transform);
        if (model->flags & 0x400) {
            attached = model->attached;
            NNS_G3dGlbFlushP();
            NNS_G3dGeBufferOP_N(0x17, attached->matrix, 0xc);
            func_01ffe1bc(attached->transform);
        }
    }
}
