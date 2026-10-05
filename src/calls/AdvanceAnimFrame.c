#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimClip {
    u8 pad_00[4];
    u16 frameCount;
} AnimClip;

typedef struct AnimState {
    fx32 frame;
    u32 unk_04;
    AnimClip *clip;
} AnimState;

typedef struct AnimPlayer {
    u8 pad_00[8];
    AnimState *state;
    BOOL finished;
    u8 pad_10[0x44];
    int loopsLeft;
    fx32 speed;
} AnimPlayer;

void AdvanceAnimFrame(AnimPlayer *player)
{
    AnimState *state;
    fx32 end;

    player->state->frame += player->speed;
    state = player->state;
    end = state->clip->frameCount << 12;
    if (state->frame >= end) {
        if (player->loopsLeft == 0) {
            state->frame = end;
            player->finished = TRUE;
        } else {
            state->frame = 0;
            player->loopsLeft--;
            if (player->loopsLeft < 0) {
                player->loopsLeft = -1;
            }
        }
    } else {
        player->finished = FALSE;
    }
}
