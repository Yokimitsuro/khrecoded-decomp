#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x34 - 0x04];
    s32 callbackTiming;
    void *callback;
} RenderObj;

typedef struct {
    u8 pad_00[0x24];
    RenderObj renderObj;
} ModelState;

typedef struct {
    u8 bytes[0x2c];
} SharedRecord;

typedef struct {
    u8 bytes[0x230];
} ModelSet;

typedef struct {
    u8 pad_0000[0x230];
    ModelState *model;
    u8 pad_0234[0x694 - 0x234];
    u8 stepState[0x6b8 - 0x694];
    void *workBuffer;
    u8 pad_06bc[0x76c - 0x6bc];
    SharedRecord records[3];
    u8 bigObj[0x930 - 0x7f0];
    u8 recordSlot;
    u8 pad_0931[0x998 - 0x931];
    u8 recordLists[0x9d4 - 0x998];
    ModelSet modelSets[2];
    u8 effectBank[0xec4 - 0xe34];
    u8 effectSet[0x1524 - 0xec4];
    u8 bufferSlots[0x16f0 - 0x1524];
    u8 attachedModels[0x1744 - 0x16f0];
    void *extraBuffer;
    u8 pad_1748[0x1824 - 0x1748];
    void *halfBuffer;
} Actor;

extern void NNS_G3dRenderObjResetCallBack(void *renderObj);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ReleaseSharedRecordState(void *record);
extern void ReleaseEffectBank(void *bank);
extern void ReleaseModelSet(void *set);
extern void EffectSet_Release(void *set);
extern void BufferSlotSet_FreeAll(void *slots);
extern void FreeRecordListsAndBuffer(void *lists);
extern void Actor_FreeAttachedModels(Actor *actor, void *models);
extern void TeardownBigObj(void *obj);
extern int FSi_DefaultStepDoneA(void *state);
extern void ShutdownRecordSlotByIndex(int slot);
extern void func_ov021_020a894c(void);
extern int ZeroHalfThenFree(void *buffer);
extern void func_ov001_0206c720(void *tag);
extern void func_ov059_020cbea0(void);

void Actor_ReleaseResources(Actor *actor)
{
    RenderObj *renderObj;
    int i;

    NNS_G3dRenderObjResetCallBack(&actor->model->renderObj);
    renderObj = &actor->model->renderObj;
    if (renderObj->callback == NULL) {
        renderObj->flags &= ~1;
    }
    renderObj->callbackTiming = 0;
    NNSi_FndFreeFromDefaultHeap(actor->workBuffer);
    for (i = 0; i < 3; i++) {
        ReleaseSharedRecordState(&actor->records[i]);
    }
    ReleaseEffectBank(actor->effectBank);
    for (i = 0; i < 2; i++) {
        ReleaseModelSet(&actor->modelSets[i]);
    }
    EffectSet_Release(actor->effectSet);
    BufferSlotSet_FreeAll(actor->bufferSlots);
    FreeRecordListsAndBuffer(actor->recordLists);
    Actor_FreeAttachedModels(actor, actor->attachedModels);
    NNSi_FndFreeFromDefaultHeap(actor->extraBuffer);
    TeardownBigObj(actor->bigObj);
    FSi_DefaultStepDoneA(actor->stepState);
    ShutdownRecordSlotByIndex(actor->recordSlot);
    func_ov021_020a894c();
    ZeroHalfThenFree(actor->halfBuffer);
    func_ov001_0206c720(func_ov059_020cbea0);
}
