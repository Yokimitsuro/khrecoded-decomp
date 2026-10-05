#include "nitro/types.h"

typedef struct NamedEntry {
    char name[0xc];
    u32 value;
    void *data;
} NamedEntry;

typedef struct CollisionWorld {
    u8 pad_00[0x820];
    NamedEntry *namedEntries;
    int namedEntryCount;
} CollisionWorld;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern CollisionWorld *data_0206083c;

void AllocWorldNamedEntries(int count)
{
    data_0206083c->namedEntries = NNSi_FndAllocFromDefaultHeap(count * sizeof(NamedEntry));
    data_0206083c->namedEntryCount = count;
}
