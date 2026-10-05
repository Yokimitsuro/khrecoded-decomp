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
    u8 pad_18[0x20];
    u8 slotIndex;
    u8 pad_39[0x1F];
    int phase;
    u8 pad_5C[0x4];
    fx32 timer;
    fx32 duration;
    int unk_68;
} Gimmick;

extern int func_ov008_020a0e10(Gimmick *gimmick);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);

static inline void Gimmick_SetBlend(Gimmick *gimmick, u16 trackIndex, s16 blendIndex)
{
    AnimModel *model = &gimmick->work->model;

    selectJointAnimationBlend(model, trackIndex, model->blendTable, blendIndex);
}

int Gimmick_WaitOpenDelay(Gimmick *gimmick)
{
    gimmick->timer += 0x1000;
    if (gimmick->timer >= gimmick->duration) {
        gimmick->update = func_ov008_020a0e10;
        gimmick->phase = 1;
        gimmick->unk_68 = 0;
        ActorSlot_SetFlag8ByIndex(gimmick->slotIndex, TRUE);
        gimmick->timer = 0;
        Gimmick_SetBlend(gimmick, 0, 0);
        Gimmick_SetBlend(gimmick, 2, 0);
        Gimmick_SetBlend(gimmick, 4, 0);
    }
    return 0;
}
