#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x0e];
    u8 level;
    u8 pad_0f;
    u16 values[4];
} NamedEntry;

typedef struct {
    u8 pad_00[0x10];
    NamedEntry entry;
} OverlaySelectionRecord;

typedef struct {
    u8 pad_00[0x08];
    s32 value;
    u8 pad_0c[0x14];
    s32 nameIndex;
    s32 level;
} SlotPair0Entry;

typedef struct {
    u8 pad_0000[0x2db4];
    u16 entryId;
} GameState;

extern GameState *data_0205fe0c;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void PackNamedRecordEntry(NamedEntry *out, int index, int nameId);
extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL func_02051e10(s32 slot);
extern SlotPair0Entry *GetRecordSlotPair0Entry(s32 index);

void FillSelectionRecordFromGroup(void)
{
    NamedEntry *entry;
    u16 entryId;
    SlotPair0Entry *slot;
    int groupBase;
    int i = 0;

    entry = &GetOverlaySelectionRecord(i)->entry;
    entryId = data_0205fe0c->entryId;

    AcquireRecordManager();
    AcquireRecordSlot(i, 1);
    slot = GetRecordSlotPair0Entry(entryId);
    PackNamedRecordEntry(entry, slot->nameIndex, i);
    entry->level = slot->level - 1;
    groupBase = (entryId - 0xd0) / 5 * 5 + 0xd0;
    for (; i < 4; i++) {
        entry->values[i] = GetRecordSlotPair0Entry(groupBase + i)->value;
    }
    func_02051e10(0);
    ReleaseRecordManager();
}
