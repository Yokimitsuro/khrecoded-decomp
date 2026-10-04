typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef volatile u32 REGType32v;

typedef enum {
    GX_TEXSIZE_S8 = 0,
    GX_TEXSIZE_S16,
    GX_TEXSIZE_S32,
    GX_TEXSIZE_S64,
    GX_TEXSIZE_S128,
    GX_TEXSIZE_S256
} GXTexSizeS;

typedef GXTexSizeS GXTexSizeT;

typedef enum {
    GX_TEXPLTTCOLOR0_USE = 0,
    GX_TEXPLTTCOLOR0_TRNS = 1
} GXTexPlttColor0;

typedef enum {
    GX_OBJVRAMMODE_CHAR_2D = 0,
    GX_OBJVRAMMODE_CHAR_1D_32K = 0x10,
    GX_OBJVRAMMODE_CHAR_1D_64K = 0x100010,
    GX_OBJVRAMMODE_CHAR_1D_128K = 0x200010,
    GX_OBJVRAMMODE_CHAR_1D_256K = 0x300010
} GXOBJVRamModeChar;

typedef enum {
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB = 2
} NNS_G2D_VRAM_TYPE;

typedef struct NNSG2dCharacterData {
    u16 H;
    u16 W;
    u32 pixelFmt;
    GXOBJVRamModeChar mappingType;
    u32 characterFmt;
    u32 szByte;
    void *pRawData;
} NNSG2dCharacterData;

typedef struct NNSG2dImageAttr {
    GXTexSizeS sizeS;
    GXTexSizeT sizeT;
    u32 fmt;
    BOOL bExtendedPlt;
    GXTexPlttColor0 plttUse;
    GXOBJVRamModeChar mappingType;
} NNSG2dImageAttr;

typedef struct NNSG2dImageProxy {
    u32 baseAddrOfVram[3];
    NNSG2dImageAttr attr;
} NNSG2dImageProxy;

extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern void GX_LoadOBJ(const void *src, u32 offset, u32 size);
extern void GXS_LoadOBJ(const void *src, u32 offset, u32 size);
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(const void *src, u32 offset, u32 size);
extern void GX_EndLoadTex(void);
extern void NNS_G2dSetImageLocation(NNSG2dImageProxy *image,
                                    NNS_G2D_VRAM_TYPE type,
                                    u32 address);

static inline void GX_SetOBJVRamModeChar(GXOBJVRamModeChar mode)
{
    *(REGType32v *)0x04000000 =
        (*(REGType32v *)0x04000000 & ~0x00300010) | mode;
}

static inline void GXS_SetOBJVRamModeChar(GXOBJVRamModeChar mode)
{
    *(REGType32v *)0x04001000 =
        (*(REGType32v *)0x04001000 & ~0x00300010) | mode;
}

static inline int GetPow_(u16 number)
{
    switch (number) {
    case 1: return GX_TEXSIZE_S8;
    case 2: return GX_TEXSIZE_S16;
    case 4: return GX_TEXSIZE_S32;
    case 8: return GX_TEXSIZE_S64;
    case 16: return GX_TEXSIZE_S128;
    case 32: return GX_TEXSIZE_S256;
    default: return GX_TEXSIZE_S8;
    }
}

static inline void CopyCharDataToImageAttr_(const NNSG2dCharacterData *source,
                                            NNSG2dImageAttr *destination)
{
    if (source->mappingType == GX_OBJVRAMMODE_CHAR_2D) {
        destination->sizeS = (GXTexSizeS)GetPow_(source->W);
        destination->sizeT = (GXTexSizeT)GetPow_(source->H);
    } else {
        destination->sizeS = (GXTexSizeS)source->W;
        destination->sizeT = (GXTexSizeT)source->H;
    }

    destination->fmt = source->pixelFmt;
    destination->bExtendedPlt = 0;
    destination->plttUse = GX_TEXPLTTCOLOR0_TRNS;
    destination->mappingType = source->mappingType;
}

static inline void DoLoadingToVram_(const NNSG2dCharacterData *source,
                                    u32 baseAddress,
                                    NNS_G2D_VRAM_TYPE type)
{
    DC_FlushRange(source->pRawData, source->szByte);

    switch (type) {
    case NNS_G2D_VRAM_TYPE_3DMAIN:
        GX_BeginLoadTex();
        GX_LoadTex(source->pRawData, baseAddress, source->szByte);
        GX_EndLoadTex();
        break;
    case NNS_G2D_VRAM_TYPE_2DMAIN:
        GX_LoadOBJ(source->pRawData, baseAddress, source->szByte);
        break;
    case NNS_G2D_VRAM_TYPE_2DSUB:
        GXS_LoadOBJ(source->pRawData, baseAddress, source->szByte);
        break;
    }
}

static inline void SetOBJVRamModeCharacterMapping_(NNS_G2D_VRAM_TYPE type,
                                                   GXOBJVRamModeChar mode)
{
    switch (type) {
    case NNS_G2D_VRAM_TYPE_3DMAIN:
        break;
    case NNS_G2D_VRAM_TYPE_2DMAIN:
        GX_SetOBJVRamModeChar(mode);
        break;
    case NNS_G2D_VRAM_TYPE_2DSUB:
        GXS_SetOBJVRamModeChar(mode);
        break;
    }
}

void NNS_G2dLoadImage1DMapping(const NNSG2dCharacterData *source,
                               u32 baseAddress,
                               NNS_G2D_VRAM_TYPE type,
                               NNSG2dImageProxy *image)
{
    SetOBJVRamModeCharacterMapping_(type, source->mappingType);
    DoLoadingToVram_(source, baseAddress, type);
    CopyCharDataToImageAttr_(source, &image->attr);
    NNS_G2dSetImageLocation(image, type, baseAddress);
}
