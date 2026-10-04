typedef unsigned short u16;
typedef unsigned int u32;

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

typedef enum NNSG2dScreenFormat {
    NNS_G2D_SCREENFORMAT_TEXT,
    NNS_G2D_SCREENFORMAT_AFFINE,
    NNS_G2D_SCREENFORMAT_AFFINEEXT
} NNSG2dScreenFormat;

typedef enum NNSG2dScreenColorMode {
    NNS_G2D_SCREENCOLORMODE_16x16,
    NNS_G2D_SCREENCOLORMODE_256x1
} NNSG2dScreenColorMode;

typedef enum GXBGColorMode {
    GX_BG_COLORMODE_16,
    GX_BG_COLORMODE_256
} GXBGColorMode;

typedef int GXBGScrBase;
typedef int GXBGCharBase;

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

typedef struct NNSG2dCharacterData NNSG2dCharacterData;
typedef struct NNSG2dPaletteData NNSG2dPaletteData;
typedef struct NNSG2dCharacterPosInfo NNSG2dCharacterPosInfo;
typedef struct NNSG2dPaletteCompressInfo NNSG2dPaletteCompressInfo;

extern void SetBGControlAuto(NNSG2dBGSelect bg,
                             NNSG2dScreenFormat screenFormat,
                             GXBGColorMode colorMode,
                             int screenWidth, int screenHeight,
                             GXBGScrBase screenBase,
                             GXBGCharBase characterBase);
extern void NNS_G2dBGLoadElementsEx(NNSG2dBGSelect bg,
                                    const NNSG2dScreenData *screenData,
                                    const NNSG2dCharacterData *characterData,
                                    const NNSG2dPaletteData *paletteData,
                                    const NNSG2dCharacterPosInfo *positionInfo,
                                    const NNSG2dPaletteCompressInfo *compressInfo);

static inline GXBGColorMode GetScreenColorMode(const NNSG2dScreenData *screenData)
{
    return screenData->colorMode == NNS_G2D_SCREENCOLORMODE_16x16
         ? GX_BG_COLORMODE_16 : GX_BG_COLORMODE_256;
}

static inline NNSG2dScreenFormat GetScreenFormat(const NNSG2dScreenData *screenData)
{
    return (NNSG2dScreenFormat)screenData->screenFormat;
}

void NNS_G2dBGSetupEx(NNSG2dBGSelect bg,
                      const NNSG2dScreenData *screenData,
                      const NNSG2dCharacterData *characterData,
                      const NNSG2dPaletteData *paletteData,
                      const NNSG2dCharacterPosInfo *positionInfo,
                      const NNSG2dPaletteCompressInfo *compressInfo,
                      GXBGScrBase screenBase,
                      GXBGCharBase characterBase)
{
    SetBGControlAuto(bg,
                     GetScreenFormat(screenData),
                     GetScreenColorMode(screenData),
                     screenData->screenWidth,
                     screenData->screenHeight,
                     screenBase,
                     characterBase);
    NNS_G2dBGLoadElementsEx(bg, screenData, characterData, paletteData,
                            positionInfo, compressInfo);
}
