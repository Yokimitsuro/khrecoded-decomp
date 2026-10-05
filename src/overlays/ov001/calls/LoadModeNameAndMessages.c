#include "nitro/types.h"

typedef struct {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct {
    u8 pad_00[0x1c];
    u16 *name;
    MessageSet messages;
} ModeState;

typedef struct {
    u8 pad_000[0x130];
    s16 slotIndex;
} OverlaySelectionRecord;

typedef struct {
    u8 pad_00[0x28];
    u16 *name;
} SlotEntry;

extern u16 data_ov001_0209ef88[];

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern SlotEntry *GetRecordSlotPair1Entry(s32 index);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern int Utf16Length(u16 *text);
extern u16 *Utf16CopyPadded(u16 *destination, u16 *source, int unitCount);
extern u32 func_ov001_02073634(u32 messageId);
extern void LoadPackedFileView(MessageSet *messages, u32 fileId, int compressed);

void LoadModeNameAndMessages(ModeState *state)
{
    SlotEntry *entry = GetRecordSlotPair1Entry(GetOverlaySelectionRecord(0)->slotIndex);

    if (entry == NULL) {
        state->name = NNSi_FndAllocFromDefaultHeap(4);
        Utf16CopyPadded(state->name, data_ov001_0209ef88, 2);
    } else {
        int length = Utf16Length(entry->name) + 1;
        state->name = NNSi_FndAllocFromDefaultHeap(length * 2);
        Utf16CopyPadded(state->name, entry->name, length);
    }
    LoadPackedFileView(&state->messages, func_ov001_02073634(8), 0);
}
