#include "nitro/types.h"

typedef struct {
    void *headObject;
    void *tailObject;
    u16 objectCount;
    u16 linkOffset;
} ObjectList;

typedef struct {
    void *state;
    u8 pad_04[4];
    u32 ownsState;
} SingleStateNode;

typedef struct {
    u8 pad_00[8];
    u32 ownsState;
    void *primaryState;
    void *secondaryState;
} DualStateNode;

typedef struct {
    void **entries;
    s32 entryCount;
    u8 pad_08[8];
    s32 overlayId;
    s32 entryContext;
    u8 pad_18[0x34];
    ObjectList singleStateList;
    ObjectList dualStateList;
} EntryOwner;

extern void *NNS_FndGetNextListObject(ObjectList *list, void *object);
extern void NNS_FndRemoveListObject(ObjectList *list, void *object);
extern void func_02029fac(s32 processor, s32 overlayId);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ReleaseSharedRecordState(void *state);
extern void ReleaseMemberResources(void *entry, s32 context);

void FreeEntriesAndStateLists(EntryOwner *owner)
{
    s32 i;
    SingleStateNode *single;
    SingleStateNode *nextSingle;
    DualStateNode *dual;
    DualStateNode *nextDual;

    if (owner->entryCount <= 0) {
        return;
    }
    for (i = 0; i < owner->entryCount; i++) {
        if (owner->entries[i] != NULL) {
            ReleaseMemberResources(owner->entries[i], owner->entryContext);
            NNSi_FndFreeFromDefaultHeap(owner->entries[i]);
        }
    }
    NNSi_FndFreeFromDefaultHeap(owner->entries);
    if (owner->overlayId != -1) {
        func_02029fac(0, owner->overlayId);
        owner->overlayId = -1;
    }

    single = NNS_FndGetNextListObject(&owner->singleStateList, NULL);
    while (single != NULL) {
        nextSingle = NNS_FndGetNextListObject(&owner->singleStateList, single);
        if (single->ownsState != 0) {
            ReleaseSharedRecordState(single->state);
            NNSi_FndFreeFromDefaultHeap(single->state);
        }
        NNS_FndRemoveListObject(&owner->singleStateList, single);
        NNSi_FndFreeFromDefaultHeap(single);
        single = nextSingle;
    }

    dual = NNS_FndGetNextListObject(&owner->dualStateList, NULL);
    while (dual != NULL) {
        nextDual = NNS_FndGetNextListObject(&owner->dualStateList, dual);
        if (dual->ownsState != 0) {
            ReleaseSharedRecordState(dual->primaryState);
            NNSi_FndFreeFromDefaultHeap(dual->primaryState);
            if (dual->secondaryState != NULL) {
                ReleaseSharedRecordState(dual->secondaryState);
                NNSi_FndFreeFromDefaultHeap(dual->secondaryState);
            }
        }
        NNS_FndRemoveListObject(&owner->dualStateList, dual);
        NNSi_FndFreeFromDefaultHeap(dual);
        dual = nextDual;
    }
}
