#include "nitro/types.h"

typedef struct Entry {
    u8 pad0[2];
    s8 kind;
    u8 pad3[0x154 - 3];
} Entry;

typedef struct Owner Owner;
typedef void (*EntryHandler)(Owner *owner, Entry *entry, int arg);

struct Owner {
    u8 pad00[8];
    Entry *entries;
    u8 pad0c[0x15 - 0xc];
    u8 count;
    u8 pad16[0x28 - 0x16];
    EntryHandler handlers[1];
};

void DispatchEntryKindHandlers(Owner *owner, int arg)
{
    int i;
    for (i = 0; i < owner->count; i++) {
        Entry *entry = &owner->entries[i];
        if (entry->kind != -1) {
            owner->handlers[entry->kind](owner, entry, arg);
        }
    }
}
