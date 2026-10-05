#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SceneModel {
    u8 pad_00[0xa4];
    fx32 unk_A4;
    u8 pad_A8[0x4];
    fx32 unk_AC;
    VecFx32 scale;
    u8 pad_BC[0x1c];
    u8 blendTable[0x2c];
} SceneModel;

extern void InitSharedRecordAndDispatch(void *dst, int resourceId, void *info, int count);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);

void InitSceneModel(SceneModel *model, int resourceId, u32 trackMask)
{
    InitSharedRecordAndDispatch(model, resourceId, NULL, 0xe);
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
    model->unk_AC = 512 * FX32_ONE;
    model->unk_A4 -= FX32_ONE / 8;
}
