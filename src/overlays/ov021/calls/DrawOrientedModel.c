#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x54];
    u32 flags;
} RenderState;

typedef struct {
    u8 pad_00[0x24];
    VecFx32 direction;
    u8 pad_30[0x20];
    u8 transform[0x84];
    u8 material[0xc];
    u8 model[4];
} OrientedModel;

extern const VecFx32 data_ov021_020b4fdc;
extern u8 NNS_G3dGlb_prmBaseRot[];
extern RenderState NNS_G3dGlb_prmMatColor0;
extern void MTX_Identity33_(MtxFx33 *mtx);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void NNS_G3dGlbSetBaseScale(void *model);
extern void MI_Copy36B(const MtxFx33 *src, void *dst);
extern void NNS_G3dGlbSetBaseTrans(void *material);
extern void NNS_G3dGlbFlushVP(void);
extern void func_01ffe1bc(void *transform);

void DrawOrientedModel(OrientedModel *model)
{
    MtxFx33 rotation;
    VecFx32 side;
    VecFx32 up;
    VecFx32 forward;

    MTX_Identity33_(&rotation);
    if (model->direction.x != 0 || model->direction.y != 0 || model->direction.z != 0) {
        func_01ffaff4(&model->direction, &forward);
        VEC_CrossProduct(&data_ov021_020b4fdc, &forward, &side);
        func_01ffaff4(&side, &side);
        VEC_CrossProduct(&forward, &side, &up);
        rotation._00 = side.x;
        rotation._01 = side.y;
        rotation._02 = side.z;
        rotation._10 = up.x;
        rotation._11 = up.y;
        rotation._12 = up.z;
        rotation._20 = forward.x;
        rotation._21 = forward.y;
        rotation._22 = forward.z;
    }
    NNS_G3dGlbSetBaseScale(model->model);
    MI_Copy36B(&rotation, NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
    NNS_G3dGlbSetBaseTrans(model->material);
    NNS_G3dGlbFlushVP();
    func_01ffe1bc(model->transform);
}
