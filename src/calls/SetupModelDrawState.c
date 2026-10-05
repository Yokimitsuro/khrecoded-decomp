#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 pad_00[0x88];
    u32 polygonAttr;
    u8 pad_8c[0x38];
    VecFx32 scale;
    u8 pad_d0[4];
    u32 flags;
} GeometryState;

typedef struct ModelDrawObject {
    u8 pad_00[0x78];
    void *model;
    u8 pad_7c[0x28];
    VecFx32 translation;
} ModelDrawObject;

extern void MI_Copy36B(const void *src, void *dst);
extern u32 NNS_G3dMdlGetMdlPolygonID(void *model, u32 materialIndex);
extern u32 NNS_G3dMdlGetMdlLightEnableFlag(void *model, u32 materialIndex);
extern u32 NNS_G3dMdlGetMdlPolygonMode(void *model, u32 materialIndex);
extern void NNS_G3dGlbFlushP(void);
extern MtxFx33 NNS_G3dGlb_prmBaseRot;
extern VecFx32 NNS_G3dGlb_prmBaseTrans;
extern GeometryState NNS_G3dGlb;

void SetupModelDrawState(ModelDrawObject *object, fx32 scale, const MtxFx33 *rotation, u32 alpha) {
    u32 polygonId;
    u32 lightMask;
    u32 polygonMode;
    void *model;

    MI_Copy36B(rotation, &NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmBaseTrans = object->translation;
    NNS_G3dGlb.scale.x = scale;
    NNS_G3dGlb.scale.y = scale;
    NNS_G3dGlb.scale.z = scale;
    model = object->model;
    NNS_G3dGlb.flags &= ~0xa4;
    polygonId = NNS_G3dMdlGetMdlPolygonID(model, 0);
    lightMask = NNS_G3dMdlGetMdlLightEnableFlag(object->model, 0);
    polygonMode = NNS_G3dMdlGetMdlPolygonMode(object->model, 0);
    NNS_G3dGlb.polygonAttr = lightMask | (polygonMode << 4) | 0xc0 | (polygonId << 24) | (alpha << 16);
    NNS_G3dGlbFlushP();
}
