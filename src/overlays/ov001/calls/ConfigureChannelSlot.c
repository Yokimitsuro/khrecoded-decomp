#include "nitro/types.h"

typedef struct ChannelSlot {
    u8 pad_00[0x10];
    s8 index;
    u8 active;
    u8 value;
    u8 pad_13;
    s32 elapsed;
    u8 pad_18[0x8];
    s32 unk_20;
    u8 pad_24[0x4];
} ChannelSlot;

typedef struct ChannelManager {
    u32 unk_00;
    ChannelSlot primary;
    ChannelSlot slots[3];
} ChannelManager;

extern ChannelManager *data_ov001_020a04b8;

void ConfigureChannelSlot(int kind, int value, int index)
{
    ChannelManager *manager = data_ov001_020a04b8;
    ChannelSlot *slot = NULL;

    if (manager == NULL) {
        return;
    }
    switch (kind) {
    case 0:
        slot = &manager->primary;
        break;
    case 1:
        slot = &manager->slots[index];
        break;
    }
    if (slot == NULL) {
        return;
    }
    if (value == 0) {
        slot->active = 0;
        slot->index = -1;
        slot->unk_20 = 0;
        return;
    }
    slot->value = value;
    slot->index = index;
    slot->active = 1;
    slot->elapsed = 0;
}
