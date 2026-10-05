#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0xa4];
    VecFx32 translation;
    VecFx32 scale;
    u8 pad_bc[0xd8 - 0xbc];
    u8 blendTable[4];
} MenuModel;

extern void InitSharedRecordAndDispatch(void *dst, u32 resourceKey, void *info, int b);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);

void InitMenuModel(MenuModel *model, u32 resourceKey, u32 trackMask)
{
    InitSharedRecordAndDispatch(model, resourceKey, NULL, 0xe);
    model->scale.z = 10 * FX32_ONE;
    model->scale.y = 10 * FX32_ONE;
    model->scale.x = 10 * FX32_ONE;
    if (trackMask & 1) {
        selectJointAnimationBlend(model, 0, model->blendTable, 0);
    }
    if (trackMask & 2) {
        selectJointAnimationBlend(model, 1, model->blendTable, 0);
    }
    if (trackMask & 4) {
        selectJointAnimationBlend(model, 2, model->blendTable, 0);
    }
    if (trackMask & 8) {
        selectJointAnimationBlend(model, 3, model->blendTable, 0);
    }
    if (trackMask & 0x10) {
        selectJointAnimationBlend(model, 4, model->blendTable, 0);
    }
    model->translation.z = 512 * FX32_ONE;
    model->translation.x -= FX32_ONE / 8;
}
