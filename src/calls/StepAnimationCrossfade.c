#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 frame;
    fx32 ratio;
} BlendAnimation;

typedef struct {
    u16 flags;
    s16 selectedIndex0;
    u8 pad_04[0x08];
    BlendAnimation *boundAnim0;
    u8 pad_10[0xca - 0x10];
    s16 pendingIndex0;
    BlendAnimation *pendingAnim0;
    fx32 fadeRemaining;
    fx32 fadeStep;
} AnimationSwapState;

extern void CommitPendingAnimationSwap(AnimationSwapState *state);

void StepAnimationCrossfade(AnimationSwapState *state)
{
    fx32 remaining = state->fadeRemaining - state->fadeStep;
    s16 pendingIndex;
    BlendAnimation *current;
    BlendAnimation *pending;
    fx32 inverse;
    state->fadeRemaining = remaining;
    if (remaining < 0) {
        remaining = 0;
    }
    pendingIndex = state->pendingIndex0;
    inverse = 0x1000 - remaining;
    current = state->boundAnim0;
    pending = state->pendingAnim0;
    if (pendingIndex >= 0) {
        current->ratio = remaining;
        pending->ratio = inverse;
    }
    if (remaining <= state->fadeStep) {
        CommitPendingAnimationSwap(state);
    }
}
