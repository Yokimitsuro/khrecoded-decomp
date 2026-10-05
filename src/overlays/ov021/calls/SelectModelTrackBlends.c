#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x08];
    u8 bindingState[0xD8];
    u8 blendTable[0x40];
} AnimatedModel;

extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern int *func_01ffb2f8(void *animationState, u16 trackIndex, int frame);

void SelectModelTrackBlends(AnimatedModel *model, int blendIndex)
{
    int trackIndex;

    for (trackIndex = 0; trackIndex < 5; trackIndex++) {
        selectJointAnimationBlend(model->bindingState, trackIndex, model->blendTable, (s16)blendIndex);
        func_01ffb2f8(model->bindingState, trackIndex, 0);
    }
}
