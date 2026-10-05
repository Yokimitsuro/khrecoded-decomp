#include "nitro/types.h"

typedef struct AnimSlot {
    u8 pad_00[0x24];
    u8 alpha;
    u8 pad_25[0xb];
} AnimSlot;

typedef struct AnimSet {
    AnimSlot *slots;
    s8 slotCount;
    u8 pad_05[0xb];
    s8 current;
    u8 state;
    u8 phase;
    u8 pad_13[5];
    int speed;
    int target;
    int elapsed;
    int reverse;
} AnimSet;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void func_0202c6a4(int arg0);
extern void *SND_RegisterSeq(int a, int b);
extern int ReleaseSharedRecordSlot(void *slot);
extern int *AcquireOrRefreshResourceBlock(void *info, void *textureHeader, int flag);
extern int IndexedPointer_GetFirstWord(int *objectBase, int recordIndex);
extern int NestedPointer_GetFirstWord(int *objectBase, int recordIndex, int entryIndex);
extern s32 func_ov001_02063a38(void);
extern void SetSlotKeyAndRebind(AnimSlot *slot, int key, int flag);

void LoadAnimSetSlots(AnimSet *set, int recordId, int mode)
{
    int *objectBase;
    void *info;
    int i;

    info = SND_RegisterSeq(recordId, 0x11);
    func_0202c6a4(0);
    objectBase = AcquireOrRefreshResourceBlock(info, NULL, 1);
    func_0202c6a4(1);
    set->slotCount = IndexedPointer_GetFirstWord(objectBase, 7);
    if (mode == 0 && func_ov001_02063a38() != 6) {
        set->slotCount--;
    }
    set->slots = NNSi_FndAllocFromDefaultHeap(set->slotCount * 0x30);
    for (i = 0; i < set->slotCount; i++) {
        AnimSlot *slots = set->slots;
        SetSlotKeyAndRebind(&slots[i], NestedPointer_GetFirstWord(objectBase, 7, i), 0);
        slots[i].alpha = 0x3f;
    }
    ReleaseSharedRecordSlot(info);
    set->current = -1;
    set->state = 0;
    set->elapsed = 0;
    switch (mode) {
    case 0:
        set->speed = 0x1800;
        set->phase = 0;
        set->target = 0xc000;
        set->reverse = 0;
        break;
    case 1:
        set->phase = 0;
        set->speed = 0x8cd;
        set->target = 0;
        set->reverse = 1;
        break;
    }
}
