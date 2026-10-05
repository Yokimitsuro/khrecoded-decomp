#include "nitro/types.h"
#include "nnsys/g3d.h"

extern u16 SampleAnimationScalarITCM(const NNSG3dResMatCAnm *pAnm, u32 info, u32 frame);
extern u16 GetMatColAnmuAlphaValue_(const NNSG3dResMatCAnm *pAnm, u32 info, u32 frame);

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return NULL;
    }
}

static inline void GetMatColAnm(const NNSG3dResMatCAnm *pAnm, u16 idx, u32 frame, NNSG3dMatAnmResult *pResult)
{
    u16 diffuse, ambient, emission, specular, polygonAlpha;
    const NNSG3dResDictMatCAnmData *pAnmData =
        (const NNSG3dResDictMatCAnmData *)GetResDataByIdx(&pAnm->dict, idx);

    diffuse = SampleAnimationScalarITCM(pAnm, pAnmData->diffuse, frame);
    ambient = SampleAnimationScalarITCM(pAnm, pAnmData->ambient, frame);
    pResult->prmMatColor0 = (u32)(diffuse | (ambient << 16) | (((pResult->prmMatColor0 & 0x8000) != 0) << 15));

    emission = SampleAnimationScalarITCM(pAnm, pAnmData->emission, frame);
    specular = SampleAnimationScalarITCM(pAnm, pAnmData->specular, frame);
    pResult->prmMatColor1 = (u32)(specular | (emission << 16) | (((pResult->prmMatColor1 & 0x8000) != 0) << 15));

    polygonAlpha = GetMatColAnmuAlphaValue_(pAnm, pAnmData->polygon_alpha, frame);
    pResult->prmPolygonAttr = (pResult->prmPolygonAttr & ~0x001f0000) | (polygonAlpha << 16);
}

void NNSi_G3dAnmCalcNsBma(NNSG3dMatAnmResult *pResult, const NNSG3dAnmObj *pAnmObj, u32 dataIdx)
{
    const NNSG3dResMatCAnm *pMatAnm = (const NNSG3dResMatCAnm *)pAnmObj->resAnm;
    fx32 frame = pAnmObj->frame;
    u32 wholeFrame;
    if (frame >= (s32)(pMatAnm->numFrame << 12)) {
        frame = (pMatAnm->numFrame << 12) - 1;
    } else if (frame < 0) {
        frame = 0;
    }
    wholeFrame = (u32)(frame >> 12);
    GetMatColAnm(pMatAnm, (u16)dataIdx, wholeFrame, pResult);
}
