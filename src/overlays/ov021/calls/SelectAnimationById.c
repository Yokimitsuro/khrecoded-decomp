#include "nitro/types.h"

typedef int (*AnimLookup)(int id);

typedef struct {
    u8 pad_000[0xd8];
    u8 blendTable[0x40];
    AnimLookup lookup;
    int currentId;
    s32 frame;
    s32 playing;
} AnimSelector;

extern void selectJointAnimationBlend(AnimSelector *selector, u16 trackIndex, void *blendTable, s16 blendIndex);

void SelectAnimationById(AnimSelector *selector, int id)
{
    int index = selector->lookup(id);

    if (index >= 0 && selector->currentId == id) {
        index = -1;
    }
    if (index >= 0) {
        selector->playing = 1;
        selector->frame = 0;
        selector->currentId = id;
        selectJointAnimationBlend(selector, 0, selector->blendTable, index);
    } else {
        selector->playing = 0;
        selector->currentId = -1;
    }
}
