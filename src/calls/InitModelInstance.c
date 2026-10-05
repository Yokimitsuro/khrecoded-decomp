#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy;
    u16 ofsEntry;
} ResDict;

typedef struct ResDictEntryHeader {
    u16 sizeUnit;
    u16 sizeName;
    u8 data[4];
} ResDictEntryHeader;

typedef struct ResMdlSet {
    u32 header[2];
    ResDict dict;
} ResMdlSet;

typedef struct ModelResList {
    u8 pad_00[8];
    void *texSet;
} ModelResList;

typedef struct ModelInstance {
    u16 flags;
    s16 animId[5];
    void *anim[5];
    u8 renderObj[0x54];
    ModelResList *resList;
    void *resMdl;
    u16 frame;
    u16 frameSpeed;
    fx32 rotation[9];
    VecFx32 translation;
    VecFx32 scale;
    VecFx32 offset;
    s16 jointId;
    s16 animSlot;
    u8 pad_cc[4];
    int userA;
    int userB;
    u8 animBlock[0xc];
    int animCount;
} ModelInstance;

extern void func_0202c6a4(int useDefault);
extern void *AcquireOrRefreshResourceBlock(ModelResList *list, int texFlag, int fileId);
extern void func_0202d410(void *file, void *texSet, int texSource);
extern void *NestedPointer_GetFirstWord(void *archive, int memberIndex, int subIndex);
extern ResMdlSet *NNS_G3dGetMdlSet(void *header);
extern void NNS_G3dRenderObjInit(void *renderObj, void *resMdl);
extern void BindModelAnimations(void *animBlock, ModelInstance *inst, void *archive, int texSource);
extern void MTX_Identity33_(fx32 *matrix);

static inline void *GetResDataByIdx(const ResDict *dict, u32 idx)
{
    if (dict != 0 && idx < dict->numEntry) {
        const ResDictEntryHeader *hdr = (const ResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)&hdr->data[idx * hdr->sizeUnit];
    }
    return 0;
}

static inline void *GetMdlByIdx(const ResMdlSet *mdlSet, u32 idx)
{
    if (mdlSet) {
        const u32 *data = GetResDataByIdx(&mdlSet->dict, idx);
        if (data) {
            return (u8 *)mdlSet + *data;
        }
    }
    return 0;
}

BOOL InitModelInstance(ModelInstance *inst, int texFlag, int hasTexSource, int fileId, int texSource)
{
    void *file;
    int i;

    if (texFlag != 0 || (hasTexSource != 0 && fileId != 0)) {
        func_0202c6a4(0);
    }
    file = AcquireOrRefreshResourceBlock(inst->resList, texFlag, fileId);
    if (texFlag == 0) {
        if (hasTexSource != 0) {
            if (fileId != 0) {
                func_0202c6a4(1);
            }
            func_0202d410(file, inst->resList->texSet, texSource);
        }
    } else {
        func_0202c6a4(1);
    }
    inst->resMdl = GetMdlByIdx(NNS_G3dGetMdlSet(NestedPointer_GetFirstWord(file, 7, 0)), 0);
    NNS_G3dRenderObjInit(inst->renderObj, inst->resMdl);
    inst->animCount = 0;
    BindModelAnimations(inst->animBlock, inst, file, texSource);
    for (i = 0; i < 5; i++) {
        inst->animId[i] = -1;
        inst->anim[i] = 0;
    }
    inst->animSlot = -1;
    inst->frame = 0;
    inst->frameSpeed = 0;
    MTX_Identity33_(inst->rotation);
    inst->translation.x = inst->translation.y = inst->translation.z = 0;
    inst->scale.x = inst->scale.y = inst->scale.z = 0x1000;
    inst->flags = 0;
    inst->offset.x = inst->offset.y = inst->offset.z = 0;
    inst->jointId = -1;
    inst->userA = 0;
    inst->userB = 0;
    return TRUE;
}
