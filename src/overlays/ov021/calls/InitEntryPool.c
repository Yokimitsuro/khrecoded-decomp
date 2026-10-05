#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5c];
    s8 group;
    u8 pad_5d[3];
} EntryDesc;

typedef void (*EntryCallback)(void);

typedef struct {
    u8 pad_00[8];
    void *slots;
    EntryDesc *descs;
    int descCount;
    u8 slotCount;
    u8 freeCount;
    u8 pad_16[2];
    EntryCallback spawn;
    EntryCallback dispatch;
    EntryCallback process;
    EntryCallback release;
    EntryCallback advance;
    EntryCallback move;
    EntryCallback animate;
} EntryPool;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void SpawnUnitFromDesc(void);
extern void DispatchEntryKindHandlers(void);
extern void ProcessActiveEntries(void);
extern void ReleaseEntryGroup(void);
extern void AdvanceAnimationCounter(void);
extern void UpdateEffectMovePhase(void);
extern void UpdateEffectAnimationPhase(void);

void InitEntryPool(EntryPool *pool, EntryDesc *descs, int descCount, int slotCount)
{
    int i;

    pool->descCount = descCount;
    pool->descs = NNSi_FndAllocFromDefaultHeap(descCount * sizeof(EntryDesc));
    for (i = 0; i < descCount; i++) {
        MI_CpuCopy8(&descs[i], &pool->descs[i], sizeof(EntryDesc));
        if (pool->descs[i].group == 0) {
            pool->descs[i].group = slotCount;
        }
    }
    pool->slots = NNSi_FndAllocFromDefaultHeap(slotCount * 0x154);
    pool->slotCount = slotCount;
    pool->freeCount = slotCount;
    pool->spawn = SpawnUnitFromDesc;
    pool->dispatch = DispatchEntryKindHandlers;
    pool->process = ProcessActiveEntries;
    pool->release = ReleaseEntryGroup;
    pool->advance = AdvanceAnimationCounter;
    pool->move = UpdateEffectMovePhase;
    pool->animate = UpdateEffectAnimationPhase;
}
