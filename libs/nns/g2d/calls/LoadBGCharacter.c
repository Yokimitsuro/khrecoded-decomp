typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef volatile unsigned short REGType16v;
typedef volatile unsigned int REGType32v;

#define NULL ((void *)0)
#define GX_DMA_NOT_USE ((u32)~0)

typedef enum GXTexFmt {
    GX_TEXFMT_NONE = 0,
    GX_TEXFMT_A3I5 = 1,
    GX_TEXFMT_PLTT4 = 2,
    GX_TEXFMT_PLTT16 = 3,
    GX_TEXFMT_PLTT256 = 4
} GXTexFmt;

typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3
} NNSG2dBGSelect;

typedef struct NNSG2dCharacterData {
    u16 height;
    u16 width;
    GXTexFmt pixelFmt;
    int mappingType;
    u32 characterFmt;
    u32 szByte;
    void *pRawData;
} NNSG2dCharacterData;

typedef struct NNSG2dCharacterPosInfo {
    u16 srcPosX;
    u16 srcPosY;
    u16 srcW;
    u16 srcH;
} NNSG2dCharacterPosInfo;

typedef union GXCharFmt16 {
    u8 data[32];
} GXCharFmt16;

typedef union GXCharFmt256 {
    u8 data[64];
} GXCharFmt256;

extern u32 GXi_DmaId;
extern REGType16v * const NNSiG2dBGCNTTable[];
extern void DC_FlushRange(const void *startAddress, u32 size);
extern void MIi_DmaCopy16(u32 dmaNo, const void *source, void *destination,
                          u32 size, BOOL waitForCompletion);
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

static inline void NNSi_G2dDmaCopy16(u32 dmaNo, const void *source,
                                     void *destination, u32 size)
{
    if (dmaNo > 3) {
        dmaNo = GX_DMA_NOT_USE;
    }
    if (dmaNo != GX_DMA_NOT_USE) {
        MIi_DmaCopy16(dmaNo, source, destination, size, 1);
    } else {
        MIi_CpuCopy16(source, destination, size);
    }
}

static inline REGType16v *GetBGnCNT(NNSG2dBGSelect bg)
{
    return NNSiG2dBGCNTTable[bg];
}

static inline BOOL IsMainBG(NNSG2dBGSelect bg)
{
    return bg <= NNS_G2D_BGSELECT_MAIN3;
}

static inline int GetBGCharOffset(void)
{
    return 0x10000 * ((*(REGType32v *)0x04000000 & 0x07000000) >> 24);
}

static inline void *GetBGnCharPtr(NNSG2dBGSelect bg)
{
    const int baseBlock = 0x4000 * ((*GetBGnCNT(bg) & 0x003c) >> 2);
    return (void *)((IsMainBG(bg) ? 0x06000000 + GetBGCharOffset()
                                  : 0x06200000) + baseBlock);
}

static inline void LoadBGnChar(NNSG2dBGSelect bg, const void *source,
                               u32 offset, u32 size)
{
    const u32 address = (u32)GetBGnCharPtr(bg);
    NNSi_G2dDmaCopy16(GXi_DmaId, source, (void *)(address + offset), size);
}

void LoadBGCharacter(NNSG2dBGSelect bg,
                     const NNSG2dCharacterData *characterData,
                     const NNSG2dCharacterPosInfo *positionInfo)
{
    u32 offset = 0;

    if (positionInfo != NULL) {
        const int offsetChars = positionInfo->srcPosY * positionInfo->srcW;
        const u32 characterSize = characterData->pixelFmt == GX_TEXFMT_PLTT256
                                ? sizeof(GXCharFmt256) : sizeof(GXCharFmt16);
        offset = offsetChars * characterSize;
    }

    DC_FlushRange(characterData->pRawData, characterData->szByte);
    LoadBGnChar(bg, characterData->pRawData, offset, characterData->szByte);
}
