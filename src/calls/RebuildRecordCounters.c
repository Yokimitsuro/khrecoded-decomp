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

typedef struct SlotPair0Entry
{
    u8 pad_00[0x18];
    u16 unk_18;
    u8 pad_1A[0x2E];
} SlotPair0Entry;

typedef struct CachedSlot
{
    int state;
    int value;
    RecordEntry entry;
} CachedSlot;

typedef struct RecordCounters
{
    u16 categoryCounts[0x80];
    u16 totalCount;
    u16 freeCount;
    CachedSlot slots[16];
} RecordCounters;

extern u8 *data_0205fe0c;
extern RecordCounters data_0205fec4;
extern u16 gRecordCounters[2];
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern SlotPair0Entry *GetRecordSlotPair0Entry(s32 index);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL func_02051e10(s32 slot);
extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern void RefreshSlotRecordCache(void);

static inline BOOL IsCategoryIndex(int index)
{
    return index >= 0 && index <= 0x7f;
}

void RebuildRecordCounters(void)
{
    u8 *itemCounts = data_0205fe0c + 0x28d8;
    RecordEntry *entry = (RecordEntry *)(data_0205fe0c + 0x2e00);
    RecordCounters *counters = &data_0205fec4;
    u16 index = 0;
    u16 remaining;

    func_01ff88c4(counters, 0, sizeof(RecordCounters));
    AcquireRecordManager();
    AcquireRecordSlot(0, 1);
    gRecordCounters[1] = 600;
    do
    {
        if (IsCategoryIndex(index))
        {
            SlotPair0Entry *info = GetRecordSlotPair0Entry(index);
            if (*itemCounts == 0 && info->unk_18 < 9999)
            {
                counters->freeCount--;
            }
        }
        index++;
        itemCounts++;
    } while (index < 0x200);

    remaining = 600;
    do
    {
        if (entry->active)
        {
            counters->categoryCounts[entry->category]++;
            counters->totalCount++;
        }
        remaining--;
        entry++;
    } while (remaining > 0);

    RefreshSlotRecordCache();
    func_02051e10(0);
    ReleaseRecordManager();
}
