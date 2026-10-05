#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimationInfo {
    u8 pad_00[4];
    u16 frameCount;
} AnimationInfo;

typedef struct AnimationTrack {
    fx32 frame;
    fx32 ratio;
    AnimationInfo *info;
} AnimationTrack;

typedef struct AnimationSwapState {
    u16 flags;
    s16 selectedIndex[5];
    AnimationTrack *boundAnim[5];
    u8 pad_20[0xca - 0x20];
    s16 pendingIndex0;
    AnimationTrack *pendingAnim0;
} AnimationSwapState;

extern void StepAnimationCrossfade(AnimationSwapState *state);

u16 AdvanceAnimationTracks(AnimationSwapState *state, fx32 delta)
{
    AnimationTrack *track;
    u16 loopedMask = 0;
    int i;

    if (state->flags & 4) {
        StepAnimationCrossfade(state);
    }
    if (!(state->flags & 2)) {
        for (i = 0; i < 5; i++) {
            if (state->selectedIndex[i] >= 0) {
                fx32 length;

                track = state->boundAnim[i];
                length = track->info->frameCount << 12;

                if (!(state->flags & 4)) {
                    track->frame += delta;
                }
                if (track->frame >= length) {
                    if ((state->flags & 4) && i == 0) {
                        track->frame = length;
                    } else {
                        loopedMask |= (1 << i);
                        track->frame -= length;
                    }
                }
            }
            if ((state->flags & 4) && i == 0 && state->pendingIndex0 >= 0) {
                AnimationTrack *pending = state->pendingAnim0;
                fx32 pendingLength = pending->info->frameCount << 12;

                pending->frame += delta;
                if (pending->frame >= pendingLength) {
                    loopedMask |= (1 << i);
                    pending->frame = pendingLength;
                }
            }
        }
    }
    return loopedMask;
}
