#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    s32 index;
    u32 value;
} ActiveEntryState;

extern volatile u32 data_020569d8[];
extern volatile ActiveEntryState gVBlankCallbackState;

void SelectActiveEntry(int index)
{
    volatile u16 *ime = (volatile u16 *)0x04000208;
    u16 oldIme = *ime;

    *ime = 0;
    gVBlankCallbackState.index = index;
    gVBlankCallbackState.value = data_020569d8[index];
    if (oldIme != 0) {
        (void)*ime;
        *ime = 1;
    }
}
