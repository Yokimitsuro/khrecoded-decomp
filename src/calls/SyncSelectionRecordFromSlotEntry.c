#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_001[0x12f];
    u16 unk_130;
    u8 pad_132[2];
    u8 unk_134;
} OverlaySelectionRecord;

typedef struct {
    u8 pad_00[0x20];
    s32 unk_20;
} SlotPair0Entry;

typedef struct {
    u8 pad_0000[0x2db6];
    u16 unk_2DB6;
} GameState;

extern GameState *data_0205fe0c;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern SlotPair0Entry *GetRecordSlotPair0Entry(s32 index);

void SyncSelectionRecordFromSlotEntry(void)
{
    OverlaySelectionRecord *record = GetOverlaySelectionRecord(0);
    u16 entryIndex = data_0205fe0c->unk_2DB6;

    AcquireRecordManager();
    AcquireRecordSlot(0, 1);
    record->unk_130 = GetRecordSlotPair0Entry(entryIndex)->unk_20;
    record->unk_134 = 0;
    ReleaseRecordSlot(0);
    ReleaseRecordManager();
}
