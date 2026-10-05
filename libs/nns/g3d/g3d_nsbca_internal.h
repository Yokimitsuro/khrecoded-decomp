#ifndef G3D_NSBCA_INTERNAL_H
#define G3D_NSBCA_INTERNAL_H

#include "libs/nns/g3d/g3d_kernel_internal.h"
#include "libs/nns/g3d/g3d_glbstate_internal.h"

#define NNS_G3D_JNTANM_SRTINFO_NODE_SHIFT 24
#define NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE 0x00000001
#define NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO 0x00000002
#define NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO 0x00000004
#define NNS_G3D_SRTFLAG_TRANS_ZERO 0x0001
#define NNS_G3D_SRTFLAG_ROT_ZERO 0x0002
#define NNS_G3D_SRTFLAG_PIVOT_EXIST 0x0008

typedef struct NNSG3dResJntAnmSRTTag_ {
    u32 tag;
} NNSG3dResJntAnmSRTTag;

typedef struct NNSG3dResJntAnm_ {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u16 numNode;
    u32 flag;
    u32 ofsRot3;
    u32 ofsRot5;
} NNSG3dResJntAnm;

typedef struct NNSG3dResDictNodeData_ {
    u32 offset;
} NNSG3dResDictNodeData;

typedef struct NNSG3dResNodeData_ {
    u16 flag;
    fx16 _00;
} NNSG3dResNodeData;

typedef struct NNSG3dJntAnmResult_ {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} NNSG3dJntAnmResult;

typedef void (*NNSG3dFuncAnmJnt)(
    NNSG3dJntAnmResult *,
    const NNSG3dAnmObj *,
    u32);

typedef void (*NNSG3dGetJointScale)(
    NNSG3dJntAnmResult *,
    const fx32 *,
    const u8 *,
    u32);

typedef struct NNSG3dRS_ {
    u8 *c;
    NNSG3dRenderObj *pRenderObj;
    u32 flag;
    NNSG3dSbcCallBackFunc cbVecFunc[32];
    u8 cbVecTiming[32];
    u8 currentNode;
    u8 currentMat;
    u8 currentNodeDesc;
    u8 dummy_;
    void *pMatAnmResult;
    NNSG3dJntAnmResult *pJntAnmResult;
    void *pVisAnmResult;
    u32 isMatCached[2];
    u32 isScaleCacheOne[2];
    u32 isEvpCached[2];
    const NNSG3dResNodeInfo *pResNodeInfo;
    const void *pResMat;
    const void *pResShp;
    fx32 posScale;
    fx32 invPosScale;
    NNSG3dGetJointScale funcJntScale;
} NNSG3dRS;

extern NNSG3dFuncAnmJnt NNS_G3dFuncAnmJntNsBcaDefault;
extern NNSG3dRS *NNS_G3dRS;

extern void MIi_CpuClear16(u16 value, void *destination, u32 size);

static inline void MI_CpuFill16(void *destination, u16 value, u32 size)
{
    MIi_CpuClear16(value, destination, size);
}

static inline void MI_CpuClear16(void *destination, u32 size)
{
    MI_CpuFill16(destination, 0, size);
}

static inline NNSG3dResNodeInfo *NNS_G3dGetNodeInfo(
    const NNSG3dResMdl *model)
{
    if (model != NULL) {
        return (NNSG3dResNodeInfo *)&model->nodeInfo;
    }
    return NULL;
}

static inline NNSG3dResNodeData *NNS_G3dGetNodeDataByIdx(
    const NNSG3dResNodeInfo *nodeInfo,
    u32 index)
{
    NNSG3dResDictNodeData *data;

    if (nodeInfo != NULL) {
        data = NNS_G3dGetResDataByIdx(&nodeInfo->dict, index);
        if (data != NULL) {
            return (NNSG3dResNodeData *)((u8 *)nodeInfo + data->offset);
        }
    }
    return NULL;
}

#endif
