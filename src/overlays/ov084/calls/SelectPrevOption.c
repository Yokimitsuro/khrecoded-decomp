#include "nitro/types.h"

extern u16 data_02060500;
extern void PlaySoundEffect(int channel, int id);

void SelectPrevOption(u8 *selection)
{
    do {
        if (*selection == 0) {
            if ((data_02060500 & 0x40) == 0) {
                return;
            }
            *selection = 2;
        }
        *selection = *selection - 1;
    } while ((1 << *selection & (u32)selection[1]) == 0);
    PlaySoundEffect(0, 0);
    selection[2] = 1;
}
