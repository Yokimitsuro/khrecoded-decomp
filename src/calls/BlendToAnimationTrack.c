#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimationResource {
    u8 header[4];
    u16 frameCount;
} AnimationResource;

typedef struct AnimationObject {
    fx32 frame;
    fx32 ratio;
    AnimationResource *resource;
} AnimationObject;

typedef struct AnimationBlendTable {
    u16 animationCounts[5];
    u8 pad_0A[0x10 - 0x0A];
    AnimationObject **animationChoices[5];
} AnimationBlendTable;

typedef struct AnimationFadeState {
    u16 flags;
    s16 selectedIndices[5];
    AnimationObject *boundAnimations[5];
    u8 renderObject[0xca - 0x20];
    s16 pendingIndex;
    AnimationObject *pendingAnimation;
    fx32 outgoingWeight;
    fx32 incomingStep;
    AnimationBlendTable defaultTable;
} AnimationFadeState;

extern void CommitPendingAnimationSwap(AnimationFadeState *state);
extern void selectJointAnimationBlend(AnimationFadeState *state, u16 trackIndex, AnimationBlendTable *table, s16 blendIndex);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void NNS_G3dRenderObjAddAnmObj(void *renderObject, AnimationObject *animation);

void BlendToAnimationTrack(AnimationFadeState *state, u16 trackIndex, AnimationBlendTable *table, s16 blendIndex, int frameCount)
{
    AnimationObject *target;

    if (table == NULL) {
        table = &state->defaultTable;
    }
    if ((state->flags & 4) && trackIndex == 0) {
        CommitPendingAnimationSwap(state);
    }
    if (frameCount == 0 || state->selectedIndices[trackIndex] < 0 || trackIndex != 0) {
        selectJointAnimationBlend(state, trackIndex, table, blendIndex);
        return;
    }
    target = table->animationChoices[trackIndex][blendIndex];
    if (frameCount > (int)(target->resource->frameCount << 12) >> 12) {
        selectJointAnimationBlend(state, trackIndex, table, blendIndex);
        return;
    }
    if (state->boundAnimations[trackIndex] == target) {
        return;
    }
    if (trackIndex != 0) {
        return;
    }
    state->pendingIndex = blendIndex;
    state->incomingStep = FX_Div(0x1000, frameCount << 12);
    state->outgoingWeight = 0x1000 - state->incomingStep;
    state->pendingAnimation = table->animationChoices[trackIndex][blendIndex];
    state->pendingAnimation->frame = 0;
    NNS_G3dRenderObjAddAnmObj(state->renderObject, state->pendingAnimation);
    state->boundAnimations[trackIndex]->ratio = state->outgoingWeight;
    state->pendingAnimation->ratio = 0x1000 - state->outgoingWeight;
    state->flags |= 4;
}
