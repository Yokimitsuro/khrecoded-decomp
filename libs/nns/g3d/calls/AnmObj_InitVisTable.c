#include "nitro/types.h"
#include "nnsys/g3d.h"

extern void *NNS_G3dFuncAnmMatNsBtaDefault;
extern void MIi_CpuClear16(u16 data, void *dst, u32 size);
extern int NNS_G3dGetResDictIdxByName(const NNSG3dResDict *dict, const NNSG3dResName *name);

static inline const NNSG3dResName *GetResNameByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (NNSG3dResName *)((u8 *)hdr + hdr->ofsName + sizeof(NNSG3dResName) * idx);
    } else {
        return NULL;
    }
}

static inline int GetMatIdxByName(const NNSG3dResMat *mat, const NNSG3dResName *name)
{
    if (mat)
        return NNS_G3dGetResDictIdxByName(&mat->dict, name);
    else
        return -1;
}

static inline NNSG3dResMat *GetMat(const NNSG3dResMdl *mdl)
{
    if (mdl && mdl->ofsMat != 0)
        return (NNSG3dResMat *)((u8 *)mdl + mdl->ofsMat);
    else
        return NULL;
}

void AnmObj_InitVisTable(NNSG3dAnmObj *anmObj, void *resAnm, const NNSG3dResMdl *mdl)
{
    u32 i;
    NNSG3dResTexSRTAnm *texSrtAnm = (NNSG3dResTexSRTAnm *)resAnm;
    const NNSG3dResMat *mat = GetMat(mdl);

    anmObj->funcAnm = NNS_G3dFuncAnmMatNsBtaDefault;
    anmObj->numMapData = mdl->info.numMat;
    MIi_CpuClear16(0, &anmObj->mapData[0], sizeof(u16) * anmObj->numMapData);

    for (i = 0; i < texSrtAnm->dict.numEntry; ++i) {
        const NNSG3dResName *name = GetResNameByIdx(&texSrtAnm->dict, i);
        int idx = GetMatIdxByName(mat, name);
        if (!(idx < 0)) {
            anmObj->mapData[idx] = (u16)(i | NNS_G3D_ANMOBJ_MAPDATA_EXIST);
        }
    }
}
