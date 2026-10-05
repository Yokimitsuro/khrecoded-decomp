#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ProjMatrix {
    fx32 m[16];
} ProjMatrix;

typedef struct GlobalStateTail {
    u8 pad_00[0x54];
    u32 flags;
} GlobalStateTail;

typedef struct ObjectModel {
    u8 pad_00[0x14];
    u8 sceneNode[0xa4];
} ObjectModel;

typedef struct DepthObject {
    u8 pad_00[0xc];
    ObjectModel *model;
    u8 pad_10[0x38];
    fx32 depth;
} DepthObject;

extern ProjMatrix NNS_G3dGlb_projMtx;
extern GlobalStateTail NNS_G3dGlb_prmMatColor0;
extern s16 data_020536c0[];
extern void func_ov042_020bd110(void);
extern int FX_Mul(int left, int right);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void func_01ffb12c(void *node);
extern void NNS_G3dGlbFlushP(void);

static inline void SetProjection(const ProjMatrix *matrix)
{
    MIi_CpuCopyFast(matrix, &NNS_G3dGlb_projMtx, sizeof(ProjMatrix));
    NNS_G3dGlb_prmMatColor0.flags &= ~0x50;
}

void DrawObjectWithDepthScale(DepthObject *object)
{
    ProjMatrix scaled;
    ProjMatrix saved;
    fx32 scale;

    func_ov042_020bd110();
    scale = FX_Div(0x1000, FX_Mul(-object->depth, data_020536c0[10]) + 0x1000);
    scaled = NNS_G3dGlb_projMtx;
    saved = scaled;
    scaled.m[0] = FX_Mul(scaled.m[0], scale);
    scaled.m[5] = FX_Mul(scaled.m[5], scale);
    SetProjection(&scaled);
    func_01ffb12c(object->model->sceneNode);
    SetProjection(&saved);
    NNS_G3dGlbFlushP();
}
