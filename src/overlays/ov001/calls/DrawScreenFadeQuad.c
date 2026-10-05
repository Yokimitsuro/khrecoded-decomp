#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

typedef struct GlobalStateTail {
    u8 pad_00[0x54];
    u32 flags;
} GlobalStateTail;

typedef struct FadeState {
    u8 pad_0000[0x3f00];
    s32 colorIndex;
    s32 alpha;
} FadeState;

extern FadeState *data_ov001_020a0500;
extern const VecFx32 data_ov001_0209e434;
extern const VecFx32 data_ov001_0209e440;
extern const VecFx32 data_ov001_0209e44c;
extern const VecFx32 data_ov001_0209e428;
extern const VecFx32 data_0205344c;
extern const u16 data_ov001_0209e420[];
extern u8 NNS_G3dGlb_projMtx[];
extern GlobalStateTail NNS_G3dGlb_prmMatColor0;
extern VecFx32 NNS_G3dGlb_camPos;
extern VecFx32 NNS_G3dGlb_camUp;
extern VecFx32 NNS_G3dGlb_camTarget;
extern u8 NNS_G3dGlb_cameraMtx[];
extern MtxFx33 NNS_G3dGlb_prmBaseRot;

extern void MTX_OrthoW(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, fx32 scaleW, void *mtx);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, void *mtx);
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *vec);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *vec);
extern void MTX_Identity33_(MtxFx33 *mtx);
extern void MI_Copy36B(const MtxFx33 *src, MtxFx33 *dst);
extern void NNS_G3dGlbFlushWVP(void);
extern void NNS_G3dGeBufferOP_N(int command, const u32 *params, int count);

static inline void SetOrthoProjection(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, fx32 scaleW)
{
    MTX_OrthoW(t, b, l, r, n, f, scaleW, NNS_G3dGlb_projMtx);
    NNS_G3dGlb_prmMatColor0.flags &= ~0x50;
}

static inline void SetLookAt(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target)
{
    NNS_G3dGlb_camPos = *camPos;
    NNS_G3dGlb_camUp = *camUp;
    NNS_G3dGlb_camTarget = *target;
    func_01ff9b70(camPos, camUp, target, NNS_G3dGlb_cameraMtx);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xe8;
}

static inline void SetBaseRotation(const MtxFx33 *rotation)
{
    MI_Copy36B(rotation, &NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
}

static inline void SendCommand1(int command, u32 value)
{
    u32 param = value;
    NNS_G3dGeBufferOP_N(command, &param, 1);
}

static inline void SendVertex16(fx16 x, fx16 y, fx16 z)
{
    u32 params[2];
    params[0] = (u16)x | ((u32)(u16)y << 16);
    params[1] = (u16)z;
    NNS_G3dGeBufferOP_N(0x23, params, 2);
}

void DrawScreenFadeQuad(void)
{
    FadeState *state = data_ov001_020a0500;
    VecFx32 scale;
    VecFx32 translation;
    VecFx32 camPos;
    VecFx32 target;
    VecFx32 camUp;
    MtxFx33 rotation;

    if (state->colorIndex == -1 || state->alpha == 0) {
        return;
    }
    scale = data_ov001_0209e434;
    translation = data_ov001_0209e440;
    camPos = data_ov001_0209e44c;
    target = data_0205344c;
    camUp = data_ov001_0209e428;
    SetOrthoProjection(0, 0xc0000, 0, 0x100000, 0, 0x3000, 0x400000);
    SetLookAt(&camPos, &camUp, &target);
    NNS_G3dGlbSetBaseScale(&translation);
    NNS_G3dGlbSetBaseTrans(&scale);
    MTX_Identity33_(&rotation);
    SetBaseRotation(&rotation);
    NNS_G3dGlbFlushWVP();
    SendCommand1(0x29, (state->alpha << 16) | 0x3c0000c0);
    SendCommand1(0x20, data_ov001_0209e420[state->colorIndex]);
    SendCommand1(0x40, 1);
    SendVertex16(-0x800, -0x800, 0);
    SendVertex16(0x800, -0x800, 0);
    SendVertex16(0x800, 0x800, 0);
    SendVertex16(-0x800, 0x800, 0);
    NNS_G3dGeBufferOP_N(0x41, NULL, 0);
}
