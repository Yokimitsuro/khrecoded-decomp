#include "nitro/types.h"

typedef struct {
    u32 active;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u8 pad_10[0x04];
    u32 unk_14;
    u8 pad_18[0x10];
    u16 unk_28;
} RecordEntry;

// Resets a record entry to its default state
void InitRecordEntry(RecordEntry *entry)
{
    entry->active = 1;
    entry->unk_04 = 0;
    entry->unk_08 = 0;
    entry->unk_0C = 0;
    entry->unk_14 = 0;
    entry->unk_28 = 0;
}
