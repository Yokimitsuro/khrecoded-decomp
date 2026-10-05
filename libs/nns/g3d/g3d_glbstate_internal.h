#ifndef G3D_GLBSTATE_INTERNAL_H
#define G3D_GLBSTATE_INTERNAL_H

#include "libs/nns/g3d/g3d_kernel_internal.h"
#include "nitro/fx_types.h"

typedef union MtxFx33_ {
    struct {
        fx32 _00, _01, _02;
        fx32 _10, _11, _12;
        fx32 _20, _21, _22;
    };
    fx32 m[3][3];
    fx32 a[9];
} MtxFx33;

typedef struct MtxFx43_ {
    fx32 m[4][3];
} MtxFx43;

typedef struct MtxFx44_ {
    fx32 m[4][4];
} MtxFx44;

typedef struct NNSG3dGlb_ {
    u32 cmd0;
    u32 mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    u32 cmd1;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmViewPort;
    u32 cmd2;
    MtxFx33 prmBaseRot;
    VecFx32 prmBaseTrans;
    VecFx32 prmBaseScale;
    u32 prmTexImageParam;
    u32 flag;
    MtxFx43 invCameraMtx;
    MtxFx43 srtCameraMtx;
    MtxFx43 invSrtCameraMtx;
    MtxFx43 invBaseMtx;
    MtxFx44 invProjMtx;
    MtxFx44 invCameraProjMtx;
    VecFx32 camPos;
    VecFx32 camUp;
    VecFx32 camTarget;
} NNSG3dGlb;

#define NNS_G3D_GLB_FLAG_FLUSH_WVP              0x00000001
#define NNS_G3D_GLB_FLAG_FLUSH_VP               0x00000002
#define NNS_G3D_GLB_FLAG_INVBASE_UPTODATE       0x00000004
#define NNS_G3D_GLB_FLAG_INVCAMERA_UPTODATE     0x00000008
#define NNS_G3D_GLB_FLAG_INVPROJ_UPTODATE       0x00000010
#define NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE 0x00000020
#define NNS_G3D_GLB_FLAG_INVCAMERAPROJ_UPTODATE 0x00000040
#define NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE    0x00000080

extern NNSG3dGlb NNS_G3dGlb;

#endif
