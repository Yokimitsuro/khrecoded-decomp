#include "nitro/types.h"

typedef struct HandleDef {
    u8 pad0[2];
    u8 slot;
    u8 pad3[0x8d];
} HandleDef;

typedef struct HandleSet {
    u8 pad0[0x10];
    u32 *handles;
    int handleCount;
    u8 pad18[0x54];
    HandleDef *defs;
    int defCount;
} HandleSet;

typedef struct RecordSource {
    u8 pad0[0x1c];
    int baseRecord;
    int baseSlot;
} RecordSource;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern u8 *GetOverlaySelectionRecord(u32 id);
extern int func_ov001_0206dba0(int clock);
extern u32 AcquireRecordHandle(RecordSource *source, u32 *selection, int record, u32 key);

void AcquireEntryHandles(HandleSet *set, RecordSource *source, u32 *selection)
{
    int i;
    int slot;
    int time;

    set->handleCount = set->defCount;
    set->handles = NNSi_FndAllocFromDefaultHeap(set->defCount << 2);
    time = func_ov001_0206dba0(*GetOverlaySelectionRecord(*selection) + 6);
    for (i = 0; i < set->defCount; i++) {
        slot = set->defs[i].slot - source->baseSlot;
        set->handles[i] = AcquireRecordHandle(source, selection, source->baseRecord + slot,
            ((time + 0x8000U & 0xfffffc) << 7) | 0x80000000 | (slot & 0x1ff));
    }
}
