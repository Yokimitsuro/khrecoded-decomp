#include "libs/nns/g3d/g3d_nsbca_internal.h"

void getMdlTrans_(NNSG3dJntAnmResult *result)
{
    u32 nodeIndex;
    const NNSG3dResNodeData *node;

    nodeIndex = *(NNS_G3dRS->c + 1);
    node = NNS_G3dGetNodeDataByIdx(NNS_G3dRS->pResNodeInfo, nodeIndex);

    if (node->flag & NNS_G3D_SRTFLAG_TRANS_ZERO) {
        result->flag |= NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO;
    } else {
        const fx32 *translation =
            (const fx32 *)((const u8 *)node + sizeof(NNSG3dResNodeData));

        result->trans.x = translation[0];
        result->trans.y = translation[1];
        result->trans.z = translation[2];
    }
}
