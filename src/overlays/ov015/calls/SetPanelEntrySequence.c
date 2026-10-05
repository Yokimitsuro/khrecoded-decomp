#include "nitro/types.h"

typedef struct PanelEntry {
    s16 level;
    u16 flags;
    s16 id;
    u16 sequence;
    u8 pad_08[8];
    int animSlot;
    u8 pad_14[4];
} PanelEntry;

typedef struct PanelWork {
    u8 pad_0000[0x55];
    s8 entryCount;
    u8 pad_0056[0x2e];
    PanelEntry entries[(0x65dc - 0x84) / 0x18];
    void *animOwner;
} PanelWork;

extern PanelWork *data_ov015_020812e0;
extern void SetSlotAnimSequence(void *owner, int slot, int sequence);
extern void func_0204f218(void *owner, int slot, int value);

void SetPanelEntrySequence(int index, u32 sequence)
{
    int i;

    if (index >= data_ov015_020812e0->entryCount) {
        return;
    }
    if (data_ov015_020812e0->entries[index].animSlot < 0) {
        return;
    }
    SetSlotAnimSequence(data_ov015_020812e0->animOwner, data_ov015_020812e0->entries[index].animSlot, sequence);
    data_ov015_020812e0->entries[index].sequence = sequence;
    for (i = 0; i < data_ov015_020812e0->entryCount; i++) {
        if (data_ov015_020812e0->entries[i].animSlot >= 0 && sequence == data_ov015_020812e0->entries[i].sequence) {
            func_0204f218(data_ov015_020812e0->animOwner, data_ov015_020812e0->entries[i].animSlot, 0);
        }
    }
}
