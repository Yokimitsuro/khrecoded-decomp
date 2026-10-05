#include "nitro/types.h"

extern void selectJointAnimationBlend(void *anim, u16 trackIndex, void *blendTable, short blendIndex);
extern void *func_01ffb2f8(void *anim, u16 trackIndex, int frame);

void RebindAnimTracks(s16 *anim, int blendIndex, int frame)
{
    int track;

    for (track = 0; track < 5; track++) {
        u16 trackIndex = (u16)track;

        if (anim[trackIndex + 0x6C] > 0) {
            selectJointAnimationBlend(anim, trackIndex, anim + 0x6C, blendIndex);
            func_01ffb2f8(anim, (u16)track, frame);
        }
    }
}
