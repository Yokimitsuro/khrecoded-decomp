#pragma thumb on

#include "nitro/types.h"

typedef struct {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
} NNSG3dResDict;

typedef struct {
    u16 sizeUnit;
    u16 sizeName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct {
    u16 offset;
    u16 flag;
} NNSG3dResDictPlttData;

typedef struct {
    u32 header[2];
    u32 texVramKey;
    u8 pad_0C[0x18 - 0x0C];
    u32 tex4x4VramKey;
    u8 pad_1C[0x2C - 0x1C];
    u32 plttVramKey;
    u16 sizePltt;
    u16 plttFlag;
    u16 plttOfsDict;
    u16 pad_36;
    u32 ofsPlttData;
    NNSG3dResDict dict;
} NNSG3dResTex;

extern void func_0202c6a4(int useDefault);
extern s32 func_0202d0ac(void *resource, void *heap);
extern NNSG3dResTex *NNS_G3dGetTex(void *file);

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    if (dict != 0 && idx < dict->numEntry) {
        const NNSG3dResDictEntryHeader *hdr = (const NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);

        return (void *)&hdr->data[idx * hdr->sizeUnit];
    }
    return 0;
}

int Tex0_GetTexPlttParams(u32 *out, void *file, int setup)
{
    NNSG3dResTex *tex;
    const u32 *texData;
    const NNSG3dResDictPlttData *plttData;
    u16 texBase;
    u32 plttOfs;
    u32 plttBase;

    if (setup) {
        func_0202c6a4(0);
        func_0202d0ac(file, 0);
        func_0202c6a4(1);
    }
    tex = NNS_G3dGetTex(file);
    texData = tex ? GetResDataByIdx(&tex->dict, 0) : 0;
    if (tex && tex->plttOfsDict) {
        plttData = GetResDataByIdx((const NNSG3dResDict *)((u8 *)tex + tex->plttOfsDict), 0);
    } else {
        plttData = 0;
    }
    plttOfs = plttData->offset;
    plttBase = (u16)tex->plttVramKey;
    if (((*texData) & (7 << 26)) != (5 << 26)) {
        texBase = (u16)tex->texVramKey;
    } else {
        texBase = (u16)tex->tex4x4VramKey;
    }
    if (!(plttData->flag & 1)) {
        plttOfs = plttOfs << 15 >> 16;
        plttBase = plttBase << 15 >> 16;
    }
    out[0] = ((*texData) + texBase) | (2 << 28);
    out[1] = (u16)(plttOfs + plttBase);
    return 1;
}
