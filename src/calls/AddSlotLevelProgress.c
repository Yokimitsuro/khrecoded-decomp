#include "nitro/types.h"

typedef struct RecordEntry
{
    u16 kind : 2;
    u16 unk_00_2 : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct CachedSlot
{
    int state;
    u32 value;
    RecordEntry entry;
} CachedSlot;

extern u8 *data_0205fe0c;
extern CachedSlot data_0205ffc8[16];
extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern u16 TruncateToU16(int value);

BOOL AddSlotLevelProgress(int index, u32 amount)
{
    CachedSlot *slot = &data_0205ffc8[index];
    RecordEntry *source;
    u32 progress;

    if (slot->value == 0 || slot->value == slot->entry.levelProgress || amount == 0)
    {
        return FALSE;
    }
    if (slot->state == 3)
    {
        return FALSE;
    }
    source = GetActiveRecordEntryOrNull((u16)(*(u16 *)(data_0205fe0c + index * 2 + 0x2d84) - 0x200));
    progress = source->levelProgress + amount;
    if (slot->value <= progress)
    {
        source->levelProgress = 0;
        slot->value = 0;
        slot->entry.unk_00_2 = 1;
        source->unk_00_2 = slot->entry.unk_00_2;
        return TRUE;
    }
    source->levelProgress = TruncateToU16(progress);
    return FALSE;
}
