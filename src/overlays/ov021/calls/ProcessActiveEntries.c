#include "nitro/types.h"

typedef struct Entry {
    u8 pad0[2];
    s8 id;
    u8 pad3[0x154 - 3];
} Entry;

typedef struct Owner {
    u8 pad0[8];
    Entry *entries;
    u8 pad0c[0x15 - 0xc];
    u8 count;
} Owner;

extern void DrawOrientedModel(Entry *entry);

void ProcessActiveEntries(Owner *owner)
{
    int i;
    for (i = 0; i < owner->count; i++) {
        if (owner->entries[i].id != -1) {
            DrawOrientedModel(&owner->entries[i]);
        }
    }
}
