#include "nitro/types.h"

typedef struct SlotEntry {
    void *data;
    u8 pad_04[0xc];
} SlotEntry;

typedef struct SlotSummary {
    u8 unk_00;
    u8 fromIndex;
    u8 toIndex;
    u8 isHolding;
    SlotEntry slots[8];
} SlotSummary;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0xec];
    u32 slotIds[8];
} OverlaySelectionRecord;

typedef struct SaveData {
    u8 pad_0000[0x2dc0];
    u32 slotValues[8];
} SaveData;

extern SaveData *data_0205fe0c;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void func_020290cc(int from, int to);
extern void func_01ff8dc8(const void *src, void *dst, u32 size);
extern int func_ov039_020bd644(void);
extern void SlotMenu_ReloadAllSlots(void);
extern void BuildSelectionEntryList(void);

void MoveSummarySlot(SlotSummary *summary, int from, int to)
{
    SlotEntry *slots = summary->slots;
    SlotEntry saved = slots[from];
    u32 *slotIds;
    u32 *slotValues;
    u32 savedId;
    u32 savedValue;
    int count;

    GetOverlaySelectionRecord(0);
    slotIds = GetOverlaySelectionRecord(0)->slotIds;
    slotValues = data_0205fe0c->slotValues;
    savedId = slotIds[from];
    savedValue = slotValues[from];
    summary->fromIndex = from;
    summary->toIndex = to;
    count = to - from;
    if (from >= to) {
        count = from - to;
    }
    func_020290cc(from, to);
    if (count != 0) {
        if (from < to) {
            func_01ff8dc8(&slotIds[from + 1], &slotIds[from], count * 4);
            func_01ff8dc8(&slotValues[from + 1], &slotValues[from], count * 4);
            func_01ff8dc8(&slots[from + 1], &slots[from], count * sizeof(SlotEntry));
        } else {
            func_01ff8dc8(&slotIds[to], &slotIds[to + 1], count * 4);
            func_01ff8dc8(&slotValues[to], &slotValues[to + 1], count * 4);
            func_01ff8dc8(&slots[to], &slots[to + 1], count * sizeof(SlotEntry));
        }
        slots[to] = saved;
        slotIds[to] = savedId;
        slotValues[to] = savedValue;
    }
    if (func_ov039_020bd644() == 2) {
        SlotMenu_ReloadAllSlots();
    }
    BuildSelectionEntryList();
}
