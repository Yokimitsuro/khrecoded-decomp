#include "nnsys/g3d.h"

typedef struct ModelHolder {
    u8 pad[0x78];
    NNSG3dResMdl *model;
} ModelHolder;

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx) {
    NNSG3dResDictEntryHeader *header;
    if (dict != NULL && idx < dict->numEntry) {
        header = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&header->data[0] + header->sizeUnit * idx);
    } else {
        return NULL;
    }
}

static inline NNSG3dResMat *GetMat(const NNSG3dResMdl *model) {
    if (model && model->ofsMat != 0)
        return (NNSG3dResMat *)((u8 *)model + model->ofsMat);
    else
        return NULL;
}

static inline NNSG3dResMatData *GetMatDataByIdx(const NNSG3dResMat *mat, u32 idx) {
    NNSG3dResDictMatData *data;
    if (mat) {
        data = (NNSG3dResDictMatData *)GetResDataByIdx(&mat->dict, idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return NULL;
}

u8 GetModelMaterialPolygonID(ModelHolder *holder, u32 matID) {
    NNSG3dResMdl *model = holder->model;
    NNSG3dResMatData *data;

    if (matID < model->info.numMat) {
        data = GetMatDataByIdx(GetMat(model), matID);
        if (data) {
            return (u8)((data->polyAttr & 0x3f000000) >> 24);
        }
    }
    return 0xff;
}
