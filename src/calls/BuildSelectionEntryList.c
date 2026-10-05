#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 unk_00_2 : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct {
    u8 pad_00[0x20];
    s32 id;
    s32 kind;
} SlotPair0Entry;

typedef struct {
    u8 pad_00[0x18];
    s32 value;
} SlotPair1Entry;

typedef struct {
    s16 id;
    s16 index;
    u8 level;
    u8 kind;
    u8 pad_06[2];
    s32 value;
} SelectionEntry;

typedef struct {
    SelectionEntry entries[21];
    u8 pad_fc[4];
    s32 entryCount;
} SelectionList;

typedef struct {
    u8 pad_00[0x2c];
    SelectionList list;
} OverlaySelectionRecord;

typedef struct {
    u8 pad_000[0x4e8];
    s32 levels[8];
} PartyData;

typedef struct {
    u8 pad_0000[0x28d8];
    PartyData party;
} GameState;

extern GameState *data_0205fe0c;
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern SlotPair0Entry *GetRecordSlotPair0Entry(s32 index);
extern SlotPair1Entry *GetRecordSlotPair1Entry(s32 index);
extern BOOL ResolveMergedRecordEntry(int index, RecordEntry *entry, s32 *outValue);

void BuildSelectionEntryList(void)
{
    SelectionList *list;
    PartyData *party;
    RecordEntry entry;
    s32 value;
    int i = 0;

    list = &GetOverlaySelectionRecord(i)->list;
    party = &data_0205fe0c->party;

    AcquireRecordManager();
    AcquireRecordSlot(0, 1);
    AcquireRecordSlot(1, 1);
    list->entryCount = 0;
    for (; i < 8; i++) {
        if (ResolveMergedRecordEntry(i, &entry, &value)) {
            SelectionEntry *out = &list->entries[list->entryCount];

            out->index = i;
            if (value != -1) {
                SlotPair0Entry *info = GetRecordSlotPair0Entry(value);
                out->id = info->id;
                out->level = party->levels[i];
                out->kind = info->kind;
            } else {
                out->id = GetRecordSlotPair0Entry(entry.category)->id;
                out->level = entry.level;
                out->kind = entry.kind;
                out->value = GetRecordSlotPair1Entry(out->id)->value;
            }
            list->entryCount++;
        }
    }
    ReleaseRecordSlot(1);
    ReleaseRecordSlot(0);
    ReleaseRecordManager();
}
