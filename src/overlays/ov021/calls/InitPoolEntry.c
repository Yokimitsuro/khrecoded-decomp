#include "nitro/types.h"

extern void *SND_RegisterSeq(u32 fileId, void *key);
extern void *func_0202c4a0(u32 fileId, u32 flags);
extern void func_0202edb0(u8 *object, s32 value, s32 sourceA, void *extra);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

typedef struct PoolEntry {
    u8 state;
    u8 id;
    s8 slot;
    u8 pad3;
    int timer;
    u8 pad8[0x28];
    u8 object[0x104];
    int field134;
    int field138;
    s8 field13c;
} PoolEntry;

void InitPoolEntry(PoolEntry *entry, int id, u32 fileId, u32 dataFileId)
{
    void *block = NULL;
    u16 *record = SND_RegisterSeq(fileId, (u8 *)id + 8);

    if (record[1] == 0) {
        block = func_0202c4a0(dataFileId, 0x11);
    }
    func_0202edb0(entry->object, (s32)record, (s32)block, (u8 *)id + 8);
    if (block != NULL) {
        NNSi_FndFreeFromDefaultHeap(block);
    }
    entry->id = id;
    entry->slot = -1;
    entry->timer = 0;
    entry->field138 = 0;
    entry->field13c = -1;
    entry->field134 = 0;
    entry->state = 0;
}
