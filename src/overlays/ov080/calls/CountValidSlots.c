#include "nitro/types.h"

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0x382c];
} SaveSlot;

typedef struct {
    u8 pad_00[0xd];
    u8 validSlotCount;
    u8 pad_0E[0x6a];
    SaveSlot slots[2];
} SaveSelectScreen;

extern u32 data_0205fe20;

void CountValidSlots(SaveSelectScreen *screen)
{
    int i;

    screen->validSlotCount = 0;
    for (i = 0; i < 2; i++) {
        screen->validSlotCount += (u8)(screen->slots[i].status != 0 ? 1 : 0);
    }
    data_0205fe20 = screen->validSlotCount != 0 ? 1 : 0;
}
