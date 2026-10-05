#include "nitro/types.h"

typedef struct AnimRig {
    u8 pad0[0x30];
    u8 anim[0xc];
    void *slots[5];
    u8 renderObj[0xb8];
    u8 block[0x2c];
    void *shared;
} AnimRig;

extern void NNS_G3dRenderObjRemoveAnmObj(void *renderObj, void *anim);
extern void selectJointAnimationBlend(void *anim, u16 slot, void *block, s16 blend);
extern int *func_01ffb2f8(void *anim, u16 slot, int frame);

void RebindModelAnimTracks(AnimRig *rig, int blend)
{
    u32 i = 0;

    do {
        if (rig->shared != NULL) {
            if (rig->slots[i] != NULL) {
                NNS_G3dRenderObjRemoveAnmObj(rig->renderObj, rig->slots[i]);
                rig->slots[i] = NULL;
            }
            selectJointAnimationBlend(rig->anim, i, rig->shared, (s16)blend);
        } else {
            selectJointAnimationBlend(rig->anim, i, rig->block, (s16)blend);
        }
        func_01ffb2f8(rig->anim, i, 0);
        i++;
    } while ((int)i < 5);
}
