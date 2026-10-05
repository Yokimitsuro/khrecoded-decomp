#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct { fx32 _00, _01, _10, _11; } MtxFx22;
typedef struct { fx32 x, y; } NNSG2dFVec2;
typedef struct { u32 attr01; u16 attr2; u16 _3; } GXOamAttr;
typedef struct NNSG2dCellData NNSG2dCellData;

struct DispObjFlags { unsigned int visible : 1; };

typedef struct DispObj {
    char pad00[0xc];
    NNSG2dFVec2 pos;
    char pad14[0x44 - 0x14];
    const NNSG2dCellData *pCell;
    char pad48[0x78 - 0x48];
    struct DispObjFlags flags;
    fx32 rotCos;
    fx32 rotSin;
    fx32 scaleX;
    fx32 scaleY;
} DispObj;

extern void MTX_Rot22_(MtxFx22 *pDst, fx32 sinVal, fx32 cosVal);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void MTX_ScaleApply22(const MtxFx22 *src, MtxFx22 *dst, fx32 x, fx32 y);
extern fx32 FX_Inv(fx32 v);
extern int DispObj_AddAffineParam(void *base, MtxFx22 *pMtx);
extern u16 NNS_G2dMakeCellToOams(GXOamAttr *pDstOams, u16 numDstOam, const NNSG2dCellData *pCell,
                         const MtxFx22 *pMtxSR, const NNSG2dFVec2 *pBaseTrans, u16 affineIndex,
                         BOOL bDoubleAffine);
extern void DispObj_FinishOams(void *base, DispObj *obj, GXOamAttr *pOams, u16 numOams, int affineIndex);

void DispObj_WriteOam(void *base, DispObj *obj)
{
    BOOL bAffine = 0;
    BOOL bDouble = 0;
    fx32 sx = obj->scaleX;
    fx32 sy = obj->scaleY;
    int affineIndex;
    MtxFx22 *pMtx;
    MtxFx22 mtxSR;
    MtxFx22 mtxInv;
    GXOamAttr oams[128];

    if (!obj->flags.visible) {
        return;
    }
    if (sx == 0 || sy == 0) {
        return;
    }
    if (sx < 0x1000 || sy < 0x1000) {
        bAffine = 1;
    }
    if (sx > 0x1000 || sy > 0x1000) {
        bDouble = bAffine = 1;
    }
    if (obj->rotCos != 0x1000 || obj->rotSin != 0) {
        bDouble = bAffine = 1;
    }
    if (bAffine) {
        MTX_Rot22_(&mtxSR, obj->rotSin, obj->rotCos);
        MI_CpuCopy8(&mtxSR, &mtxInv, sizeof(MtxFx22));
        MTX_ScaleApply22(&mtxSR, &mtxSR, sx, sy);
        MTX_ScaleApply22(&mtxInv, &mtxInv, FX_Inv(sx), FX_Inv(sy));
        affineIndex = DispObj_AddAffineParam(base, &mtxInv);
        pMtx = &mtxSR;
    } else {
        affineIndex = 0;
        pMtx = 0;
    }
    DispObj_FinishOams(base, obj, oams,
                  NNS_G2dMakeCellToOams(oams, 128, obj->pCell, pMtx, &obj->pos, (u16)affineIndex, bDouble),
                  affineIndex);
}
