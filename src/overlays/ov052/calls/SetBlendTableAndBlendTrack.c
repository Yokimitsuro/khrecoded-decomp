#include "nitro/types.h"

typedef struct ModelHolder {
    u8 pad_00[4];
    u8 fadeState[1];
} ModelHolder;

typedef struct AnimatedActor {
    u8 pad_000[0x230];
    ModelHolder *model;
    u8 pad_234[0x764 - 0x234];
    void *blendTable;
} AnimatedActor;

extern void BlendToAnimationTrack(void *state, u16 trackIndex, void *table, s16 blendIndex, int frameCount);

void SetBlendTableAndBlendTrack(AnimatedActor *actor, void *blendTable, int trackIndex, int blendIndex, int frameCount)
{
    if (blendTable != actor->blendTable) {
        actor->blendTable = blendTable;
    }
    BlendToAnimationTrack(actor->model->fadeState, trackIndex, actor->blendTable, blendIndex, frameCount);
}
