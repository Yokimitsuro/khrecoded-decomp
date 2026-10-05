#ifndef NNSYS_G3D_H
#define NNSYS_G3D_H

#include "libs/nns/g3d/g3d_kernel_internal.h"

typedef enum NNSG3dMatAnmResultFlag_ {
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SCALEONE = 0x00000001,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_ROTZERO = 0x00000002,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_TRANSZERO = 0x00000004,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SET = 0x00000008,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_MULT = 0x00000010,
    NNS_G3D_MATANM_RESULTFLAG_WIREFRAME = 0x00000020
} NNSG3dMatAnmResultFlag;

typedef struct NNSG3dMatAnmResult_ {
    NNSG3dMatAnmResultFlag flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmTexImage;
    u32 prmTexPltt;
    fx32 scaleS, scaleT;
    fx16 sinR, cosR;
    fx32 transS, transT;
    u16 origWidth, origHeight;
    fx32 magW, magH;
} NNSG3dMatAnmResult;

typedef struct NNSG3dResMatCAnm_ {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u16 flag;
    NNSG3dResDict dict;
} NNSG3dResMatCAnm;

typedef struct NNSG3dResDictMatCAnmData_ {
    u32 diffuse;
    u32 ambient;
    u32 specular;
    u32 emission;
    u32 polygon_alpha;
} NNSG3dResDictMatCAnmData;

typedef enum NNSG3dTexSRTElem_ {
    NNS_G3D_TEXSRTANM_ELEM_FX16 = 0x10000000,
    NNS_G3D_TEXSRTANM_ELEM_CONST = 0x20000000,
    NNS_G3D_TEXSRTANM_ELEM_STEP_1 = 0x00000000,
    NNS_G3D_TEXSRTANM_ELEM_STEP_2 = 0x40000000,
    NNS_G3D_TEXSRTANM_ELEM_STEP_4 = 0x80000000,
    NNS_G3D_TEXSRTANM_ELEM_STEP_MASK = 0xc0000000,
    NNS_G3D_TEXSRTANM_ELEM_LAST_INTERP_MASK = 0x0000ffff,
    NNS_G3D_TEXSRTANM_ELEM_LAST_INTERP_SHIFT = 0
} NNSG3dTexSRTElem;

typedef struct NNSG3dResTexSRTAnm_ {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u8 flag;
    u8 texMtxMode;
    NNSG3dResDict dict;
} NNSG3dResTexSRTAnm;

#endif
