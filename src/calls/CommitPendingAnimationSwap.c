#include "nitro/types.h"

extern void NNS_G3dRenderObjRemoveAnmObj(void *pRenderObject, void *pAnmObj);

typedef struct {
    u16 flags;
    s16 selectedIndex0;
    u8 pad_04[0x08];
    void *boundAnim0;
    u8 pad_10[0x20 - 0x10];
    u8 renderObject[0xaa];
    s16 pendingIndex0;
    void *pendingAnim0;
} AnimationSwapState;

/* Commits a queued track-0 animation swap. */
void CommitPendingAnimationSwap(AnimationSwapState *state)
{
    void *current = state->boundAnim0;
    if (current != NULL) {
        NNS_G3dRenderObjRemoveAnmObj(&state->renderObject, current);
    }

    *(s32 *)((u8 *)state->pendingAnim0 + 4) = 0x1000;
    state->boundAnim0 = state->pendingAnim0;
    state->pendingAnim0 = NULL;
    state->selectedIndex0 = state->pendingIndex0;
    state->pendingIndex0 = -1;
    state->flags &= 0xfffb;
}
