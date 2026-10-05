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
extern CollisionWorld *gActorRegistry;

void AllocWorldNamedEntries(int count)
{
    gActorRegistry->namedEntries = NNSi_FndAllocFromDefaultHeap(count * sizeof(NamedEntry));
    gActorRegistry->namedEntryCount = count;
}
