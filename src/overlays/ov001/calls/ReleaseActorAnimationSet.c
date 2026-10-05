#include "nitro/types.h"

typedef struct AnimationSet {
    u16 count[5];
    u16 texSource;
    void *archiveRecord;
    void **objects[5];
} AnimationSet;

typedef struct ActorModel {
    u8 pad_00[0xc];
    void *activeAnimation;
    u8 pad_10[0x10];
    u8 renderObj[0x54];
} ActorModel;

extern void NNS_G3dRenderObjRemoveAnmObj(void *renderObj, void *animObj);
extern void func_0202eb08(AnimationSet *animSet);
extern void func_01ff88c4(void *dst, u32 value, u32 size);

void ReleaseActorAnimationSet(AnimationSet *animSet, ActorModel *model)
{
    if (animSet->archiveRecord != NULL) {
        NNS_G3dRenderObjRemoveAnmObj(model->renderObj, model->activeAnimation);
        model->activeAnimation = NULL;
        func_0202eb08(animSet);
        func_01ff88c4(animSet, 0, sizeof(AnimationSet));
    }
}
