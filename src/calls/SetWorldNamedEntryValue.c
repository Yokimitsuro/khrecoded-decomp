#include "nitro/types.h"

typedef struct NamedEntry {
    char name[0xc];
    u32 value;
    void *data;
} NamedEntry;

typedef struct CollisionWorld {
    u8 pad_00[0x820];
    NamedEntry *namedEntries;
} CollisionWorld;

extern CollisionWorld *gActorRegistry;

void SetWorldNamedEntryValue(int index, const u32 *value)
{
    NamedEntry *entries = gActorRegistry->namedEntries;
    if (entries != NULL) {
        entries[index].value = *value;
    }
}
