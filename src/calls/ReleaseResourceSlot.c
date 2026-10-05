#include "nitro/types.h"

typedef struct ResourceSlot {
    u8 pad_00[2];
    u16 refCount;
    u16 unk_04;
    u8 pad_06[0xc - 6];
    void *group;
    void *heapBlock;
} ResourceSlot;

extern void ReleaseResourceGroup(void *group);
extern void NNS_G3dResDefaultRelease(void *pResData);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Drops a slot's refcount; at zero, releases its resource. */
BOOL ReleaseResourceSlot(ResourceSlot *slot)
{
    slot->refCount = slot->refCount - 1;
    if (slot->refCount == 0) {
        if (*(u32 *)slot->group == 0x4850414b) {
            ReleaseResourceGroup(slot->group);
        } else {
            NNS_G3dResDefaultRelease(slot->group);
        }
        slot->unk_04 = 0;
        if (slot->heapBlock != NULL) {
            NNSi_FndFreeFromDefaultHeap(slot->heapBlock);
            slot->heapBlock = NULL;
        }
        return TRUE;
    }
    return FALSE;
}
