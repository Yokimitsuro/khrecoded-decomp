#include "nitro/types.h"

typedef struct {
    u8 slotIndex;
    u8 pad_01;
    u8 needsRedraw;
    u8 pad_03;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 toggle;
} SaveSelectScreen;

extern u16 data_02060500;
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ToggleOptionOnLeft(SaveSelectScreen *screen)
{
    if ((u32)(screen->step - 1) <= 1 && (data_02060500 & 0x20)) {
        screen->toggle ^= 1;
        screen->needsRedraw = 1;
        PlaySoundEffect(0, 0);
    }
}
