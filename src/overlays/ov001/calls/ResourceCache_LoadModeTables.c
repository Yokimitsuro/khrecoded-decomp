#include "nitro/types.h"

typedef struct ModeTriple {
    u16 first;
    u16 second;
    u16 third;
} ModeTriple;

typedef struct ResourceCache {
    u8 pad_000[0x1B8];
    int idCount;
    u16 *ids;
    int tripleCount;
    ModeTriple *triples;
} ResourceCache;

extern ResourceCache *data_ov001_020a04fc;
extern s8 func_ov001_02068084(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern int GetTableEntryValue(int mode);
extern int GetSecondTableEntryValue(int mode);
extern u16 *GetTableEntryElement(int mode, int index);
extern ModeTriple *GetSecondTableTriple(int mode, int index);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

void ResourceCache_LoadModeTables(void)
{
    int idCount;
    int i;
    int mode;
    int tripleCount;
    int j;

    mode = func_ov001_02068084();

    AcquireRecordSlot(6, 1);
    idCount = GetTableEntryValue(mode);
    tripleCount = GetSecondTableEntryValue(mode);
    if (idCount != 0) {
        data_ov001_020a04fc->ids = NNSi_FndAllocFromDefaultHeap(idCount * 2);
    }
    data_ov001_020a04fc->idCount = idCount;
    if (tripleCount != 0) {
        data_ov001_020a04fc->triples = NNSi_FndAllocFromDefaultHeap(tripleCount * 6);
    }
    data_ov001_020a04fc->tripleCount = tripleCount;
    for (i = 0; i < idCount; i++) {
        u16 *entry = &data_ov001_020a04fc->ids[i];
        *entry = *GetTableEntryElement(mode, i);
    }
    for (j = 0; j < tripleCount; j++) {
        ModeTriple *entry = &data_ov001_020a04fc->triples[j];
        ModeTriple *source = GetSecondTableTriple(mode, j);
        entry->first = source->first;
        entry->second = source->second;
        entry->third = source->third;
    }
    ReleaseRecordSlot(6);
}
