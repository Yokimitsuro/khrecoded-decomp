#include "nitro/types.h"

typedef struct TaggedEntry {
    u32 id : 18;
    u32 order : 6;
    u32 value : 7;
    u32 flag : 1;
} TaggedEntry;

extern int data_020608c8[];
extern TaggedEntry *data_02060940[];

void MarkTaggedEntry(u32 id)
{
    int index;

    for (index = 0; index < data_020608c8[1]; index++) {
        TaggedEntry *entry = data_02060940[index];
        if (entry->id == id) {
            entry->flag = 1;
            return;
        }
    }
}
