#include "nitro/types.h"

typedef struct SharedRecordSlot {
    u16 refCount;
    u16 loaded;
    u16 pad_04;
    u16 pad_06;
    void *heap;
    void *data;
    void *extraBlock;
    u8 nameFlag;
} SharedRecordSlot;

extern void ReleaseResourceGroup(void *group);
extern void NNS_G3dResDefaultRelease(void *pResData);
extern void NNSi_FndFreeToExpHeap(void *block, void *heap);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

int ReleaseSharedRecordSlot(SharedRecordSlot *slot)
{
    slot->refCount--;
    if (slot->refCount == 0) {
        if (slot->loaded != 0) {
            if (*(int *)slot->data == 0x4850414b) {
                ReleaseResourceGroup(slot->data);
            } else {
                NNS_G3dResDefaultRelease(slot->data);
            }
            slot->loaded = 0;
            slot->pad_04 = 0;
        }
        slot->nameFlag = 0;
        NNSi_FndFreeToExpHeap(slot->data, slot->heap);
        slot->data = 0;
        if (slot->extraBlock != 0) {
            NNSi_FndFreeFromDefaultHeap(slot->extraBlock);
            slot->extraBlock = 0;
        }
        return 1;
    }
    return 0;
}
