#include "libs/nns/g3d/g3d_nsbca_internal.h"

void getMdlScale_(NNSG3dJntAnmResult *result)
{
    u32 nodeIndex;
    const NNSG3dResNodeData *node;
    const u8 *scale;

    nodeIndex = *(NNS_G3dRS->c + 1);
    node = NNS_G3dGetNodeDataByIdx(NNS_G3dRS->pResNodeInfo, nodeIndex);
    scale = (const u8 *)node + sizeof(*node);

    if (!(node->flag & NNS_G3D_SRTFLAG_TRANS_ZERO)) {
        scale += 3 * sizeof(fx32);
    }

    if (!(node->flag & NNS_G3D_SRTFLAG_ROT_ZERO)) {
        if (node->flag & NNS_G3D_SRTFLAG_PIVOT_EXIST) {
            scale += 2 * sizeof(fx16);
        } else {
            scale += 8 * sizeof(fx16);
        }
    }

    NNS_G3dRS->funcJntScale(
        result,
        (const fx32 *)scale,
        NNS_G3dRS->c,
        node->flag);
}
