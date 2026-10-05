#include "nitro/types.h"

typedef struct SlotState {
    u8 pad_00[6];
    u8 state;
    u8 pad_07;
} SlotState;

typedef struct SceneData {
    u8 pad_00[0xb44c8];
    SlotState slots[1];
} SceneData;

extern SceneData *gSoundWork;

BOOL IsSlotStateNotOne(int slot)
{
    return gSoundWork->slots[slot].state != 1;
}
