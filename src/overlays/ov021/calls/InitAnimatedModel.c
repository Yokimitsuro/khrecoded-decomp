#include "nitro/types.h"

typedef struct ModelResource {
    u8 pad0[0x17];
    u8 jointCount;
    u8 pad18[0x28];
    u8 nameDict[4];
} ModelResource;

typedef struct AnimatedModel {
    u8 pad0[0x24];
    ModelResource *resource;
    u8 pad28[0x2c];
    void *jointWork;
    u8 pad58[0xac];
    void *jointBuffer;
    int rootJoint;
    u8 pad10c[0xc];
    int field118;
    int field11c;
    u8 pad120[4];
    int state;
    u8 pad128[0xc];
    u8 slot;
} AnimatedModel;

extern const char sOv021_TraTg_020b5004[];
extern void InitSharedRecordAndDispatch(AnimatedModel *model, int source, int flag, void *extra);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern int NNS_G3dGetResDictIdxByName(void *dict, const char *name);

void InitAnimatedModel(AnimatedModel *model, int source, int slot)
{
    void *dict;
    void *buffer;
    int rootJoint;

    InitSharedRecordAndDispatch(model, source, 1, (u8 *)slot + 8);
    buffer = NNSi_FndAllocFromDefaultHeap(model->resource->jointCount * 0x58);
    model->jointBuffer = buffer;
    model->jointWork = buffer;
    dict = model->resource != NULL ? model->resource->nameDict : NULL;
    if (dict != NULL) {
        rootJoint = NNS_G3dGetResDictIdxByName(dict, sOv021_TraTg_020b5004);
    } else {
        rootJoint = -1;
    }
    model->rootJoint = rootJoint;
    model->state = 0;
    model->field11c = -1;
    model->slot = slot;
    model->field118 = 0;
}
