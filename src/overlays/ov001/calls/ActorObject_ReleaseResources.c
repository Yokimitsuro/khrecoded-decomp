#include "nitro/types.h"

typedef void (*ActorCallback)(u8 *actor, int arg1, int arg2);

extern void ZeroHalfThenFree(void *block);
extern void ActorSlot_UnlinkByIndex(int index);
extern void func_ov001_02088b80(u8 *work);
extern void NNS_G3dRenderObjResetCallBack(void *model);
extern u8 *GetBoundedEntryField(int index);
extern int func_ov001_02063a38(void);
extern void func_ov059_020cd274(u8 *actor);
extern void func_ov052_020d073c(u8 *actor);
extern void CommitPendingAnimationSwap(void *anim);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_0202eb08(void *resource);
extern int ActorSlot_GetByIndex(int index);
extern int ActorSlot_GetFlagsByIndex(int index);
extern void ActorSlot_SetField1C4ByIndex(int index, int value);
extern void Obj_ConditionalShutdown(void *object, int index);
extern void ReleaseResourceAndDetach(void *object);

typedef struct {
    s16 id;
    u8 pad[0x2a];
} SlotEntry;

typedef struct {
    u8 pad0[0xd4];
    SlotEntry slots[6][5];
} SlotWork;

void ActorObject_ReleaseResources(u8 *work)
{
    int i;
    int j;
    u8 *actor;
    u8 *model;
    ActorCallback callback;

    if (*(void **)(work + 0xd20) != NULL) {
        ZeroHalfThenFree(*(void **)(work + 0xd20));
        *(void **)(work + 0xd20) = NULL;
    }
    if (*(u32 *)(work + 0xef4) == 0) {
        return;
    }
    if (*(u32 *)(work + 0xef4) & 0x200) {
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 5; j++) {
                if (((SlotWork *)work)->slots[i][j].id == -2) {
                    ActorSlot_UnlinkByIndex((u16)*(u32 *)(work + 0xf00));
                    goto done_search;
                }
            }
        }
    }
done_search:
    if (!(*(u32 *)(work + 0xef4) & 0x4000)) {
        func_ov001_02088b80(work);
        if (**(u8 ***)(work + 0xd18) != NULL) {
            NNS_G3dRenderObjResetCallBack(**(u8 ***)(work + 0xd18) + 0x24);
            if (*(int *)(work + 0xf00) < 3) {
                actor = GetBoundedEntryField(*(int *)(work + 0xf00));
                if (func_ov001_02063a38() == 7) {
                    func_ov059_020cd274(actor);
                    if (*(int *)(actor + 0x75c) == 0x12) {
                        callback = *(ActorCallback *)(actor + 0x1f8);
                        if (callback != NULL) {
                            callback(actor, 0, 0);
                        }
                    }
                } else {
                    func_ov052_020d073c(actor);
                    model = **(u8 ***)(work + 0xd18);
                    if (*(u16 *)(model + 4) & 4) {
                        CommitPendingAnimationSwap(model + 4);
                    }
                    if ((*(u64 *)(actor + 0x9ac) & 0x800) == 0 && *(int *)(actor + 0x75c) != 0) {
                        callback = *(ActorCallback *)(actor + 0x1f8);
                        if (callback != NULL) {
                            callback(actor, 0, 0);
                        }
                    }
                }
            }
        }
    }
    if (!(*(u32 *)(work + 0xef4) & 0x4000) && !(*(u32 *)(work + 0xef4) & 0x8000)) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(work + 0xd18));
        *(void **)(work + 0xd18) = NULL;
    }
    if (*(u8 **)(work + 0xd1c) != NULL) {
        for (i = 0; i < 5; i++) {
            u8 *resource = *(u8 **)(work + 0xd1c) + i * 0x24;
            if (*(int *)(resource + 0xc) != 0) {
                func_0202eb08(resource);
            }
        }
        NNSi_FndFreeFromDefaultHeap(*(void **)(work + 0xd1c));
        *(void **)(work + 0xd1c) = NULL;
    }
    if (ActorSlot_GetByIndex((u16)*(u32 *)(work + 0xf00))) {
        if (ActorSlot_GetFlagsByIndex((u16)*(u32 *)(work + 0xf00))) {
            ActorSlot_SetField1C4ByIndex((u16)*(u32 *)(work + 0xf00), 0x1000);
        }
        if (!(*(u32 *)(work + 0xef4) & 0x10000)) {
            Obj_ConditionalShutdown(work + 0xd24, (u16)*(u32 *)(work + 0xf00));
        }
    }
    if (*(int *)(work + 0xc78) != 0) {
        ReleaseResourceAndDetach(work + 0xc04);
    }
    *(u32 *)(work + 0xef4) = 0;
}
