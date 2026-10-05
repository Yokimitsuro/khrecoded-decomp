#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x30];
    int pending;
    int active;
} RenderState;

typedef struct {
    u8 pad_00[0x24];
    RenderState render;
} ActorModel;

typedef struct {
    u8 pad_000[0x230];
    ActorModel *model;
    u8 pad_234[0x694 - 0x234];
    u8 record[0x6b8 - 0x694];
    void *buffer;
    u8 pad_6bc[0x76c - 0x6bc];
    u8 sharedStates[6][0x2c];
    u8 animSelector[0xb2c - 0x874];
    u8 recordLists[0xb68 - 0xb2c];
    u8 parts[2][0x230];
} ActorBase;

extern void NNS_G3dRenderObjResetCallBack(RenderState *render);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ReleaseSharedRecordState(void *state);
extern void ReleaseEffectBank(void *bank);
extern void ReleaseModelSet(void *part);
extern void FreeEntriesAndStateLists(void *container);
extern void FreeRecordListsAndBuffer(void *lists);
extern void ReleaseResourceSlotArray(ActorBase *actor, void *block);
extern void TeardownBigObj(void *selector);
extern void FSi_DefaultStepDoneA(void *record);
extern void ReleaseBigObj(void *object);
extern void ShutdownRecordSlotByIndex(int index);

void DestroyActorResources(ActorBase *actor)
{
    RenderState *render;
    int i;

    NNS_G3dRenderObjResetCallBack(&actor->model->render);
    render = &actor->model->render;
    if (render->active == 0) {
        render->flags &= ~1;
    }
    render->pending = 0;
    NNSi_FndFreeFromDefaultHeap(actor->buffer);
    for (i = 0; i < 6; i++) {
        ReleaseSharedRecordState(actor->sharedStates[i]);
    }
    ReleaseEffectBank((u8 *)actor + 0xfc8);
    for (i = 0; i < 2; i++) {
        ReleaseModelSet(actor->parts[i]);
    }
    FreeEntriesAndStateLists((u8 *)actor + 0x1070);
    FreeRecordListsAndBuffer(actor->recordLists);
    ReleaseResourceSlotArray(actor, (u8 *)actor + 0x105c);
    TeardownBigObj(actor->animSelector);
    FSi_DefaultStepDoneA(actor->record);
    ReleaseBigObj((u8 *)actor + 0x1108);
    ShutdownRecordSlotByIndex(*((u8 *)actor + 0x9b4));
}
