#include "nitro/types.h"

typedef struct {
    u32 vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy;
    u32 ofsTex;
} NNSG3dResTexInfo;

typedef struct {
    u32 vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy;
    u32 ofsTex;
    u32 ofsTexPlttIdx;
} NNSG3dResTex4x4Info;

typedef struct {
    u32 header[2];
    NNSG3dResTexInfo texInfo;
    NNSG3dResTex4x4Info tex4x4Info;
} NNSG3dResTex;

extern void (*data_02060570)(const void *src, u32 dest, u32 size);

void Tex_LoadVram(NNSG3dResTex *pTex)
{
    u32 sz;
    u32 sz4;

    sz = (u32)pTex->texInfo.sizeTex << 3;
    if (sz != 0) {
        const void *pData = (u8 *)pTex + pTex->texInfo.ofsTex;
        u32 from = (pTex->texInfo.vramKey & 0xffff) << 3;

        data_02060570(pData, from, sz);
        pTex->texInfo.flag |= 1;
    }
    sz4 = (u32)pTex->tex4x4Info.sizeTex << 3;
    if (sz4 != 0) {
        const void *pData = (u8 *)pTex + pTex->tex4x4Info.ofsTex;
        const void *pDataPlttIdx = (u8 *)pTex + pTex->tex4x4Info.ofsTexPlttIdx;
        u32 from = (pTex->tex4x4Info.vramKey & 0xffff) << 3;

        data_02060570(pData, from, sz4);
        data_02060570(pDataPlttIdx, ((from & 0x1ffff) >> 1) + 0x20000 + ((from & 0x40000) >> 2), sz4 >> 1);
        pTex->tex4x4Info.flag |= 1;
    }
}
