#include "libs/nns/g3d/g3d_nsbca_internal.h"

#define pivotUtilColumn1_ (pivotUtil_ + 1)
#define pivotUtilColumn2_ (pivotUtil_ + 2)
#define pivotUtilColumn3_ (pivotUtil_ + 3)

void getMdlRot_(NNSG3dJntAnmResult *result)
{
    u32 idxNode;
    const NNSG3dResNodeData *pNd;
    const u8 *p;

    idxNode = *(NNS_G3dRS->c + 1);
    pNd = NNS_G3dGetNodeDataByIdx(NNS_G3dRS->pResNodeInfo, idxNode);
    p = (const u8 *)pNd + sizeof(*pNd);

    if (!(pNd->flag & NNS_G3D_SRTFLAG_TRANS_ZERO)) {
        p += 3 * sizeof(fx32);
    }

    if (!(pNd->flag & NNS_G3D_SRTFLAG_ROT_ZERO)) {
        if (pNd->flag & NNS_G3D_SRTFLAG_PIVOT_EXIST) {
            fx32 A = *(fx16 *)(p + 0);
            fx32 B = *(fx16 *)(p + sizeof(fx16));
            u32 idxPivot =
                (pNd->flag & NNS_G3D_SRTFLAG_IDXPIVOT_MASK) >>
                NNS_G3D_SRTFLAG_IDXPIVOT_SHIFT;

            MI_Zero36B(&result->rot);

            result->rot.a[idxPivot] =
                (pNd->flag & NNS_G3D_SRTFLAG_PIVOT_MINUS) ?
                -FX32_ONE : FX32_ONE;

            result->rot.a[pivotUtil_[idxPivot * 4]] = A;
            result->rot.a[pivotUtilColumn1_[idxPivot * 4]] = B;
            result->rot.a[pivotUtilColumn2_[idxPivot * 4]] =
                (pNd->flag & NNS_G3D_SRTFLAG_SIGN_REVC) ? -B : B;
            result->rot.a[pivotUtilColumn3_[idxPivot * 4]] =
                (pNd->flag & NNS_G3D_SRTFLAG_SIGN_REVD) ? -A : A;
        } else {
            const fx16 *pp = (const fx16 *)p;

            result->rot.a[0] = pNd->_00;
            result->rot.a[1] = pp[0];
            result->rot.a[2] = pp[1];
            result->rot.a[3] = pp[2];
            result->rot.a[4] = pp[3];
            result->rot.a[5] = pp[4];
            result->rot.a[6] = pp[5];
            result->rot.a[7] = pp[6];
            result->rot.a[8] = pp[7];
        }
    } else {
        result->flag |= NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO;
    }
}
