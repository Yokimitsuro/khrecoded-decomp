#include "nitro/types.h"
#include "nnsys/g3d.h"

typedef struct CameraAnimResource {
    u8 pad_00[0xc];
    void *anmSet;
} CameraAnimResource;

typedef struct CameraAnim {
    u32 unk_00;
    CameraAnimResource *resource;
    NNSG3dAnmObj *anmObj;
} CameraAnim;

extern NNSG3dFuncAnmJnt NNS_G3dFuncAnmJntNsBcaDefault;
extern void *NNS_G3dGetAnmByIdx(const void *res, u32 idx);
extern void MIi_CpuClear16(u16 data, void *dest, u32 size);
extern void Obj_SetIndirectWord(CameraAnim *anim, int value);

void CamAnim_SelectAnim(CameraAnim *anim, u32 index)
{
    u32 i;
    NNSG3dResJntAnm *jntAnm = NNS_G3dGetAnmByIdx(anim->resource->anmSet, index);
    NNSG3dAnmObj *anmObj = anim->anmObj;
    u16 *ofsArray;

    anmObj->frame = 0;
    anmObj->next = NULL;
    anmObj->priority = 0x7f;
    anmObj->ratio = FX32_ONE;
    anmObj->resTex = NULL;
    anmObj->resAnm = jntAnm;
    anmObj->funcAnm = NNS_G3dFuncAnmJntNsBcaDefault;
    anmObj->numMapData = 2;
    MIi_CpuClear16(0, &anmObj->mapData[0], sizeof(u16) * anmObj->numMapData);
    ofsArray = (u16 *)((u8 *)jntAnm + sizeof(NNSG3dResJntAnm));
    for (i = 0; i < jntAnm->numNode; i++) {
        NNSG3dResJntAnmSRTTag *tag = (NNSG3dResJntAnmSRTTag *)((u8 *)jntAnm + ofsArray[i]);
        anmObj->mapData[i] = (u16)((tag->tag >> NNS_G3D_JNTANM_SRTINFO_NODE_SHIFT) | NNS_G3D_ANMOBJ_MAPDATA_EXIST);
    }
    Obj_SetIndirectWord(anim, 0);
}
