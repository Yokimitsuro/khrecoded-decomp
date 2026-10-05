#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimModel {
    u8 bindingState[0xD8];
    u8 blendTable[0x10];
} AnimModel;

typedef struct GimmickWork {
    u8 pad_00[0x14];
    AnimModel model;
} GimmickWork;

typedef struct Gimmick {
    u8 pad_00[0xC];
    GimmickWork *work;
    u8 pad_10[0x4];
    int (*update)(struct Gimmick *gimmick);
    u8 pad_18[0x28];
    VecFx32 position;
    u8 pad_4c[0xc];
    int phase;
} Gimmick;

extern int Anim_GetFrame(AnimModel *model, int track);
extern int func_0202f4cc(AnimModel *model, int track);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void SpawnSoundSlot(int soundId, int kind, const VecFx32 *position, int flags);
extern int func_ov008_020a0e88(Gimmick *gimmick);

static inline void Gimmick_SetBlend(Gimmick *gimmick, u16 trackIndex, s16 blendIndex)
{
    AnimModel *model = &gimmick->work->model;

    selectJointAnimationBlend(model, trackIndex, model->blendTable, blendIndex);
}

int Gimmick_WaitOpenAnimEnd(Gimmick *gimmick)
{
    int frame = Anim_GetFrame(&gimmick->work->model, 0);

    if (frame + 0x1000 >= func_0202f4cc(&gimmick->work->model, 0)) {
        gimmick->phase = 2;
        gimmick->update = func_ov008_020a0e88;
        Gimmick_SetBlend(gimmick, 0, 1);
        Gimmick_SetBlend(gimmick, 2, 1);
        Gimmick_SetBlend(gimmick, 4, 1);
        SpawnSoundSlot(0x1a1, 4, &gimmick->position, 2);
    }
    return 0;
}
