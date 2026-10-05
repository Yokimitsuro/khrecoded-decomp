#include "nitro/types.h"

typedef struct {
    u16 flags;
    s16 frames[5];
    void *anims[5];
    u8 renderObj[1];
} AnimTrackSet;

extern void NNS_G3dRenderObjRemoveAnmObj(void *renderObj, void *anim);
extern void selectJointAnimationBlend(AnimTrackSet *tracks, u16 trackIndex, void *blendTable, s16 blendIndex);
extern int *func_01ffb2f8(AnimTrackSet *tracks, u16 trackIndex, int frame);

void RebindAnimTracks_020aef84(AnimTrackSet *tracks, void *blendTable, int blendIndex)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (tracks->anims[i] != NULL) {
            NNS_G3dRenderObjRemoveAnmObj(tracks->renderObj, tracks->anims[i]);
            tracks->anims[i] = NULL;
        }
        selectJointAnimationBlend(tracks, i, blendTable, (s16)blendIndex);
        func_01ffb2f8(tracks, i, 0);
    }
}
