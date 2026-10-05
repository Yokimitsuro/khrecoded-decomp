#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct NNSG3dResMdl NNSG3dResMdl;

typedef struct G3dGlobalState {
    u8 pad_00[0x94];
    MtxFx33 baseRot;
    VecFx32 baseTrans;
    VecFx32 baseScale;
    u32 unk_D0;
    u32 flags;
} G3dGlobalState;

typedef struct ShadowVolume {
    VecFx32 position;
    fx32 scale;
    NNSG3dResMdl **modelRef;
    u8 alpha;
    u8 pad_15;
    u16 rotY;
} ShadowVolume;

extern G3dGlobalState NNS_G3dGlb;
extern const fx16 data_02053580[];

extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void NNS_G3dGlbFlushP(void);
extern void NNS_G3dMdlSetMdlPolygonID(NNSG3dResMdl *model, u32 matId, int polygonId);
extern void NNS_G3dMdlSetMdlCullMode(NNSG3dResMdl *model, u32 matId, int cullMode);
extern void NNS_G3dMdlSetMdlAlpha(NNSG3dResMdl *model, u32 matId, int alpha);
extern void NNS_G3dMdlSetMdlPolygonMode(NNSG3dResMdl *model, u32 matId, int polygonMode);
extern void NNS_G3dDraw1Mat1Shp(const NNSG3dResMdl *model, u32 materialId, u32 shapeId, BOOL sendMaterial);

void ShadowVolume_Draw(ShadowVolume *shadow)
{
    NNSG3dResMdl *model = *shadow->modelRef;
    int angle;

    if (model == NULL) {
        return;
    }
    NNS_G3dGlb.baseScale.x = NNS_G3dGlb.baseScale.y = NNS_G3dGlb.baseScale.z = shadow->scale;
    NNS_G3dGlb.baseTrans = shadow->position;
    angle = shadow->rotY >> 4;
    MTX_RotY33_(&NNS_G3dGlb.baseRot, data_02053580[angle],
                        data_02053580[(0x400 - angle) & 0xfff]);
    NNS_G3dGlb.flags &= ~0xa4;
    NNS_G3dGlbFlushP();

    NNS_G3dMdlSetMdlPolygonID(model, 0, 0);
    NNS_G3dMdlSetMdlCullMode(model, 0, 1);
    NNS_G3dMdlSetMdlAlpha(model, 0, shadow->alpha);
    NNS_G3dMdlSetMdlPolygonMode(model, 0, 3);
    NNS_G3dDraw1Mat1Shp(model, 0, 0, TRUE);

    NNS_G3dMdlSetMdlPolygonID(model, 0, 0x3f);
    NNS_G3dMdlSetMdlCullMode(model, 0, 3);
    NNS_G3dMdlSetMdlAlpha(model, 0, shadow->alpha);
    NNS_G3dMdlSetMdlPolygonMode(model, 0, 3);
    NNS_G3dDraw1Mat1Shp(model, 0, 0, TRUE);

    NNS_G3dGlb.baseScale.x = NNS_G3dGlb.baseScale.y = NNS_G3dGlb.baseScale.z = FX32_ONE;
    NNS_G3dGlb.flags &= ~0xa4;
}
