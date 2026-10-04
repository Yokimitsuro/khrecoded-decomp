typedef unsigned int u32;
typedef int BOOL;

typedef enum {
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB = 2
} NNS_G2D_VRAM_TYPE;

typedef struct NNSG2dPaletteData {
    u32 fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

typedef struct NNSG2dImagePaletteProxy {
    u32 fmt;
    BOOL bExtendedPlt;
    u32 baseAddrOfVram[3];
} NNSG2dImagePaletteProxy;

extern void DC_FlushRange(const void *address, u32 size);
extern void GX_BeginLoadTexPltt(void);
extern void GX_LoadTexPltt(const void *source, u32 address, u32 size);
extern void GX_EndLoadTexPltt(void);
extern void GX_LoadOBJPltt(const void *source, u32 address, u32 size);
extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_LoadOBJExtPltt(const void *source, u32 address, u32 size);
extern void GX_EndLoadOBJExtPltt(void);
extern void GXS_LoadOBJPltt(const void *source, u32 address, u32 size);
extern void GXS_BeginLoadOBJExtPltt(void);
extern void GXS_LoadOBJExtPltt(const void *source, u32 address, u32 size);
extern void GXS_EndLoadOBJExtPltt(void);
extern void NNS_G2dSetImagePaletteLocation(NNSG2dImagePaletteProxy *image,
                                           NNS_G2D_VRAM_TYPE type,
                                           u32 address);

void NNS_G2dLoadPalette(const NNSG2dPaletteData *source,
                        u32 address,
                        NNS_G2D_VRAM_TYPE type,
                        NNSG2dImagePaletteProxy *palette)
{
    void *rawData = source->pRawData;
    u32 size = source->szByte;

    DC_FlushRange(rawData, size);
    switch (type) {
    case NNS_G2D_VRAM_TYPE_2DMAIN:
        if (source->bExtendedPlt != 0) {
            GX_BeginLoadOBJExtPltt();
            GX_LoadOBJExtPltt(rawData, address, size);
            GX_EndLoadOBJExtPltt();
        } else {
            GX_LoadOBJPltt(rawData, address, size);
        }
        break;
    case NNS_G2D_VRAM_TYPE_2DSUB:
        if (source->bExtendedPlt != 0) {
            GXS_BeginLoadOBJExtPltt();
            GXS_LoadOBJExtPltt(rawData, address, size);
            GXS_EndLoadOBJExtPltt();
        } else {
            GXS_LoadOBJPltt(rawData, address, size);
        }
        break;
    case NNS_G2D_VRAM_TYPE_3DMAIN:
        GX_BeginLoadTexPltt();
        GX_LoadTexPltt(rawData, address, size);
        GX_EndLoadTexPltt();
        break;
    }

    palette->fmt = source->fmt;
    palette->bExtendedPlt = source->bExtendedPlt;
    NNS_G2dSetImagePaletteLocation(palette, type, address);
}
