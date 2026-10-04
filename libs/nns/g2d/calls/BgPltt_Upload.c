typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

#define NULL ((void *)0)
#define GX_DMA_NOT_USE ((u32)~0)
#define HW_BG_PLTT ((void *)0x05000000)
#define HW_DB_BG_PLTT ((void *)0x05000400)

typedef enum GXTexFmt {
    GX_TEXFMT_NONE = 0,
    GX_TEXFMT_A3I5 = 1,
    GX_TEXFMT_PLTT4 = 2,
    GX_TEXFMT_PLTT16 = 3,
    GX_TEXFMT_PLTT256 = 4
} GXTexFmt;

typedef enum NNSG2dBGExtPlttSlot {
    NNS_G2D_BGEXTPLTTSLOT_MAIN0,
    NNS_G2D_BGEXTPLTTSLOT_MAIN1,
    NNS_G2D_BGEXTPLTTSLOT_MAIN2,
    NNS_G2D_BGEXTPLTTSLOT_MAIN3,
    NNS_G2D_BGEXTPLTTSLOT_SUB0,
    NNS_G2D_BGEXTPLTTSLOT_SUB1,
    NNS_G2D_BGEXTPLTTSLOT_SUB2,
    NNS_G2D_BGEXTPLTTSLOT_SUB3
} NNSG2dBGExtPlttSlot;

typedef struct NNSG2dPaletteCompressInfo {
    u16 numPalette;
    u16 padding;
    void *paletteIndexTable;
} NNSG2dPaletteCompressInfo;

typedef struct NNSG2dPaletteData {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

typedef u16 GXBGPltt16[16];
typedef u16 GXBGPltt256[256];

extern u32 GXi_DmaId;
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

static inline u32 GetCompressedPaletteOriginalIndex(
    const NNSG2dPaletteCompressInfo *compressInfo, int index)
{
    return ((u16 *)compressInfo->paletteIndexTable)[index];
}

static inline u32 GetPaletteSize(const NNSG2dPaletteData *paletteData)
{
    switch (paletteData->fmt) {
    case GX_TEXFMT_PLTT16:
        return sizeof(GXBGPltt16);
    case GX_TEXFMT_PLTT256:
        return sizeof(GXBGPltt256);
    default:
        return 0;
    }
}

void BgPltt_Upload(NNSG2dBGExtPlttSlot slot,
                   const NNSG2dPaletteData *paletteData,
                   const NNSG2dPaletteCompressInfo *compressInfo)
{
    void *paletteBase;

    DC_FlushRange(paletteData->pRawData, paletteData->szByte);

    if (slot <= NNS_G2D_BGEXTPLTTSLOT_MAIN3) {
        paletteBase = HW_BG_PLTT;
    } else {
        paletteBase = HW_DB_BG_PLTT;
    }

    if (compressInfo != NULL) {
        const u32 paletteSize = GetPaletteSize(paletteData);
        const int paletteCount = compressInfo->numPalette;
        int i = 0;

        if (paletteCount <= 0) {
            return;
        }

        do {
            const u32 destinationOffset =
                GetCompressedPaletteOriginalIndex(compressInfo, i) * paletteSize;
            const void *source = (u8 *)paletteData->pRawData + paletteSize * i;

            NNSi_G2dDmaCopy16(GXi_DmaId, source,
                              (u8 *)paletteBase + destinationOffset, paletteSize);
            i++;
        } while (i < paletteCount);
    } else {
        NNSi_G2dDmaCopy16(GXi_DmaId, paletteData->pRawData,
                          paletteBase, paletteData->szByte);
    }
}
