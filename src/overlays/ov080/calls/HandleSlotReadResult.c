#include "nitro/types.h"

typedef struct {
    u32 words[0x3760 / 4];
} SaveData;

typedef struct {
    s32 status : 8;
    s32 frameIndex : 8;
    u32 statusHigh : 16;
    u8 pad_04[0x4a];
    u16 playTimeText;
    u8 pad_50[0x80];
    SaveData saveData;
} SaveSlot;

extern SaveData *data_0205fe0c;
extern void func_02026ef4(u32 mode);

void HandleSlotReadResult(SaveSlot *slot, int result)
{
    if (result == 2) {
        slot->status = 0;
        func_02026ef4(1);
        slot->saveData = *data_0205fe0c;
        slot->frameIndex = 0;
    } else {
        slot->status = 1;
    }
    slot->playTimeText = 0;
}
