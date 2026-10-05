#include "nitro/types.h"

typedef struct Entry {
    u8 pad0[0x154];
} Entry;

typedef struct Owner {
    void *context;
    u8 pad04[4];
    Entry *entries;
    u8 pad0c[0x15 - 0xc];
    u8 count;
} Owner;

extern void InitEntryPool(Owner *owner, int mode, int x, int y);
extern void InitPoolEntry(Entry *entry, void *context, int first, int second, int index);

void SetupOwnerAndEntries(Owner *owner, int first, int second, int mode, int x, int y)
{
    int i;

    InitEntryPool(owner, mode, x, y);
    for (i = 0; i < owner->count; i++) {
        InitPoolEntry(&owner->entries[i], owner->context, first, second, i);
    }
}
