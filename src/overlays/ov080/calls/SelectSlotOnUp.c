#include "nitro/types.h"

typedef struct {
    u8 data[0x3830];
} SaveSlot;

typedef struct {
    u8 slotIndex;
    u8 pad_01;
    u8 needsRedraw;
    u8 pad_03;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 pad_08[0x70];
    SaveSlot slots[2];
} SaveSelectScreen;

extern u16 data_02060500;
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void LoadSlotIntoGame(SaveSlot *slot);

void SelectSlotOnUp(SaveSelectScreen *screen)
{
    if (screen->step == 0 && (data_02060500 & 0x40)) {
        screen->slotIndex ^= 1;
        LoadSlotIntoGame(&screen->slots[screen->slotIndex]);
        screen->needsRedraw = 1;
        PlaySoundEffect(0, 0);
    }
}
