#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1b8];
    u8 slots[32];
} GroupEntry;

extern GroupEntry *func_ov032_020bbc80(void *group);

void SetGroupEntrySlotByte(void *group, u8 value, int slot)
{
    GroupEntry *entry = func_ov032_020bbc80(group);
    entry->slots[slot % 32] = value;
}
