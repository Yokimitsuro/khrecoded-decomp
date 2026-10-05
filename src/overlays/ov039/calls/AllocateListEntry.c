#include "nitro/types.h"

typedef struct {
    int id;
    u8 pad_0004[0x0c];
    int next;
} Ov039ListEntry;

extern int data_ov039_020bea20;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void NNS_FndAppendListObject(char *list, char *obj);

Ov039ListEntry *AllocateListEntry(int id)
{
    Ov039ListEntry *entry;

    if (id == 0) {
        return 0;
    }
    entry = (Ov039ListEntry *)NNSi_FndAllocFromDefaultHeap(sizeof(Ov039ListEntry));
    MI_CpuFill8(entry, 0, sizeof(Ov039ListEntry));
    entry->id = id;
    entry->next = 0;
    NNS_FndAppendListObject((char *)(data_ov039_020bea20 + 0xca74), (char *)entry);
    return entry;
}
