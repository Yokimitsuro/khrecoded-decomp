#include "nitro/types.h"

extern u8 *data_0205fe0c;

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
    u8 pad_00[8];
    int weight;
    u8 pad_0C[0x3C];
} SlotPair0Entry;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern SlotPair0Entry *GetRecordSlotPair0Entry(s32 index);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern int FindRangeValue(u8 first, u8 second);
extern s64 _u32_div_f(int dividend, int divisor);

BOOL ResolveMergedRecordEntry(int index, RecordEntry *entry, u32 *outValue)
{
    int firstSlot;
    int secondSlot;
    u16 firstHandle;
    u16 secondHandle;
    RecordEntry *first;
    RecordEntry *second;
    SlotPair0Entry *firstInfo;
    SlotPair0Entry *secondInfo;
    SlotPair0Entry *mergedInfo;
    int mergedCategory;
    int divisor;
    int firstWeight;
    int secondWeight;
    int level;

    firstSlot = index * 2;
    secondSlot = firstSlot + 1;
    entry->active = 0;
    *outValue = 0xffffffff;

    firstHandle = *(u16 *)(data_0205fe0c + firstSlot * 2 + 0x2d84);
    if (firstHandle == 0xffff)
    {
        return FALSE;
    }
    if (firstHandle < 0x200)
    {
        *outValue = firstHandle;
        return TRUE;
    }
    secondHandle = *(u16 *)(data_0205fe0c + secondSlot * 2 + 0x2d84);
    if (secondHandle == 0xffff)
    {
        first = GetActiveRecordEntryOrNull((u16)(firstHandle - 0x200));
        *entry = *first;
        return TRUE;
    }

    first = GetActiveRecordEntryOrNull((u16)(firstHandle - 0x200));
    second = GetActiveRecordEntryOrNull((u16)(secondHandle - 0x200));
    firstInfo = GetRecordSlotPair0Entry((u8)first->category);
    secondInfo = GetRecordSlotPair0Entry((u8)second->category);

    entry->active = 1;
    entry->kind = first->kind | second->kind;
    entry->unk_00_2 = 0;

    AcquireRecordManager();
    AcquireRecordSlot(0, 1);
    AcquireRecordSlot(5, 1);

    mergedCategory = FindRangeValue(first->category, second->category);
    if (mergedCategory == -1)
    {
        mergedCategory = FindRangeValue(second->category, first->category);
    }
    if (mergedCategory == -1)
    {
        entry->category = first->category;
        mergedInfo = firstInfo;
    }
    else
    {
        entry->category = (u8)mergedCategory;
        mergedInfo = GetRecordSlotPair0Entry(entry->category);
    }
    divisor = mergedInfo->weight;
    firstWeight = firstInfo->weight * (first->level + 1);
    secondWeight = secondInfo->weight * (second->level + 1);
    level = (int)_u32_div_f(firstWeight + secondWeight, divisor);
    entry->levelProgress = (u16)(_u32_div_f(firstWeight + secondWeight, divisor) >> 32);
    if (level > 100)
    {
        level = 100;
    }
    entry->level = (u16)level;

    ReleaseRecordSlot(5);
    ReleaseRecordSlot(0);
    ReleaseRecordManager();
    return TRUE;
}
