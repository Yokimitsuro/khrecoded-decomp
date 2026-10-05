#include "nitro/types.h"

typedef struct AnimatedModel {
    u32 flags;
    s32 timer;
    u8 fadeState[1];
} AnimatedModel;

extern void BlendToAnimationTrack(void *state, u16 trackIndex, void *table, s16 blendIndex, int frameCount);

void BlendModelAnimation(AnimatedModel *model, void *table, int trackIndex, int blendIndex, int frameCount)
{
    if (model->flags & 1) {
        BlendToAnimationTrack(model->fadeState, trackIndex, table, blendIndex, frameCount);
        model->timer = 0;
        model->flags &= ~0x400;
    }
}
