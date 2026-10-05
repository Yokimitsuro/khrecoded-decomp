#include "nitro/types.h"

typedef struct {
    s32 values[3];
} SlotTriple;

typedef struct {
    u8 pad_00[6];
    s16 mode;
} SessionHeader;

typedef struct {
    SlotTriple slots[3];
    u16 ids[3];
    s16 mode;
    u8 pad_2c[4];
    s32 param;
    u8 pad_34[4];
    u8 extra[4];
} SessionSource;

typedef struct {
    u8 pad_0000[0x208];
    SessionHeader header;
    u8 pad_0210[0x10];
    SessionSource source;
    u8 pad_025c[0x274c - 0x25c - 4];
    SlotTriple slots[3];
    u16 ids[3];
    u8 pad_2772[0x27a8 - 0x2772];
    s32 counters[3];
    u8 pad_27b4[2];
    u8 dirty : 1;
    u8 pad_bits : 7;
    u8 pad_27b7[0x2938 - 0x27b7];
    s32 param;
} SessionState;

typedef struct {
    u16 pad_00;
    u16 current;
    u16 initial;
} SelectionRecord;

extern SessionState *data_ov001_020a0480;
extern void RestoreSaveSnapshot(void *extra);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void LoadDifficultyPresetIntoSession(void);
extern int *AcquireMapLayout(BOOL reload, BOOL discard);
extern void SetupAllSelectionRecords(void);
extern void FillSelectionRecordFromGroup(void);
extern void BuildSelectionEntryList(void);
extern void SyncSelectionRecordFromSlotEntry(void);
extern void func_0204fbb4(void);
extern void RebuildRecordCounters(void);
extern void func_02050a58(void);
extern SelectionRecord *GetOverlaySelectionRecord(u32 index);

void RefreshSessionSelections(void)
{
    int i;
    SessionState *state = data_ov001_020a0480;
    SessionHeader *header = &state->header;
    SessionSource *source = &state->source;

    RestoreSaveSnapshot(source->extra);
    if (ReadSessionPackedBits(0x1a00, 2) != 3) {
        LoadDifficultyPresetIntoSession();
    }
    i = 0;
    AcquireMapLayout(1, 0);
    SetupAllSelectionRecords();
    FillSelectionRecordFromGroup();
    BuildSelectionEntryList();
    SyncSelectionRecordFromSlotEntry();
    func_0204fbb4();
    RebuildRecordCounters();
    func_02050a58();
    do {
        GetOverlaySelectionRecord(i)->current = GetOverlaySelectionRecord(i)->initial;
        state->counters[i] = 0;
        i++;
    } while (i < 3);
    i = 0;
    do {
        state->slots[i] = source->slots[i];
        state->ids[i] = source->ids[i];
        i++;
    } while (i < 3);
    header->mode = source->mode;
    state->param = source->param;
    state->dirty = 1;
}


