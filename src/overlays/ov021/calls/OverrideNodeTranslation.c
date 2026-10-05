#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x40];
    u8 nodeDict[4];
} ModelResource;

typedef struct {
    u8 pad_00[4];
    ModelResource *resMdl;
    u8 pad_08[0x24];
    void *ptrUser;
} RenderObject;

typedef struct {
    u8 *code;
    RenderObject *renderObj;
    u32 flag;
    void (*callbacks[32])(void *rs);
    u8 callbackTiming[32];
    u8 currentNode;
    u8 currentMat;
    u8 currentNodeDesc;
} RenderState;

typedef struct {
    u8 pad_000[0x134];
    VecFx32 basePosition;
} SlotMarker;

extern const u8 sOv021_EfWindB01_020b4fe8[];

extern int NNS_G3dGetResDictIdxByName(const void *dict, const void *name);
extern void NNS_G3dGetCurrentMtx(MtxFx43 *posMtx, MtxFx33 *vecMtx);
extern void NNS_G3dGeBufferOP_N(u32 op, const void *args, u32 numWords);

static inline void GeCommand1(u32 op, u32 param)
{
    NNS_G3dGeBufferOP_N(op, &param, 1);
}

void OverrideNodeTranslation(RenderState *rs)
{
    SlotMarker *marker = rs->renderObj->ptrUser;
    ModelResource *model = rs->renderObj->resMdl;
    void *dict = model != NULL ? model->nodeDict : NULL;
    int nodeIndex = dict != NULL ? NNS_G3dGetResDictIdxByName(dict, sOv021_EfWindB01_020b4fe8) : -1;
    int currentNode = (rs->flag & 0x10) ? rs->currentNodeDesc : -1;

    if (currentNode == nodeIndex) {
        MtxFx33 vecMtx;
        MtxFx43 posMtx;
        VecFx32 *trans;

        NNS_G3dGetCurrentMtx(&posMtx, &vecMtx);
        trans = &marker->basePosition;
        posMtx._30 = trans->x;
        posMtx._31 = trans->y;
        posMtx._32 = trans->z;
        GeCommand1(0x10, 2);
        NNS_G3dGeBufferOP_N(0x17, &vecMtx, 12);
        GeCommand1(0x10, 1);
        NNS_G3dGeBufferOP_N(0x17, &posMtx, 12);
        GeCommand1(0x10, 2);
        rs->callbacks[6] = NULL;
        rs->callbackTiming[6] = 0;
    }
}
