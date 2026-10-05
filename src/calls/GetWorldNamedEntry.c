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

extern CollisionWorld *data_0206083c;

NamedEntry *GetWorldNamedEntry(int index)
{
    BOOL invalid = TRUE;
    NamedEntry *entries = data_0206083c->namedEntries;
    if (entries != NULL && index != 0xff) {
        invalid = FALSE;
    }
    if (invalid) {
        return NULL;
    }
    return &entries[index];
}
