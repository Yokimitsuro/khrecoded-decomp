#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RotatedEntry {
    u8 pad_00[0x7c];
    fx32 cosine;
    fx32 sine;
    u8 pad_84[0x8];
} RotatedEntry;

typedef struct RotatedEntryTable {
    u32 unk_00;
    RotatedEntry entries[1];
} RotatedEntryTable;

extern const s16 data_02053580[];

void SetEntryRotation(RotatedEntryTable *table, int entryIndex, int angle)
{
    RotatedEntry *entry;
    int angleIndex;

    if (entryIndex < 0) {
        return;
    }
    entry = &table->entries[entryIndex];
    angleIndex = (u16)(0x10000 - angle) >> 4;
    entry->sine = data_02053580[angleIndex];
    entry->cosine = data_02053580[(0x400 - angleIndex) & 0xfff];
}
