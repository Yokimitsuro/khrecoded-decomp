#include "nitro/types.h"
#include "nnsys/g3d.h"

typedef struct SharedModel {
    NNSG3dResMdl *model;
    NNSG3dResFileHeader *file;
} SharedModel;

extern SharedModel data_02060840;
extern void *Archive_LoadFile(u32 fileId, u32 mode);
extern void func_0202c6a4(int enable);
extern s32 func_0202d0ac(void *resource, void *heap);
extern NNSG3dResMdlSet *NNS_G3dGetMdlSet(const NNSG3dResFileHeader *header);
extern void NNS_G3dMdlSetMdlLightEnableFlag(NNSG3dResMdl *model, u32 matId, int light);

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *header;
    if (dict != NULL && idx < dict->numEntry) {
        header = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&header->data[0] + header->sizeUnit * idx);
    }
    return NULL;
}

static inline NNSG3dResMdl *GetMdlByIdx(const NNSG3dResMdlSet *mdlSet, u32 idx)
{
    NNSG3dResDictMdlSetData *data;
    if (mdlSet) {
        data = (NNSG3dResDictMdlSetData *)GetResDataByIdx(&mdlSet->dict, idx);
        if (data) {
            return (NNSG3dResMdl *)((u8 *)mdlSet + data->offset);
        }
    }
    return NULL;
}

BOOL LoadSharedModel(u32 fileId)
{
    data_02060840.file = Archive_LoadFile(fileId, 0x11);
    func_0202c6a4(0);
    func_0202d0ac(data_02060840.file, NULL);
    func_0202c6a4(1);
    data_02060840.model = GetMdlByIdx(NNS_G3dGetMdlSet(data_02060840.file), 0);
    NNS_G3dMdlSetMdlLightEnableFlag(data_02060840.model, 0, 0);
    return TRUE;
}
