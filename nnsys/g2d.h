#ifndef NNSYS_G2D_H
#define NNSYS_G2D_H

#include "nitro/types.h"
#include "nitro/gx.h"

#define NNS_G2D_GLYPH_INDEX_NOT_FOUND 0xffff

typedef struct NNSG2dCharWidths {
    s8 left;
    u8 glyphWidth;
    s8 charWidth;
} NNSG2dCharWidths;

typedef struct NNSG2dFontGlyph {
    u8 cellWidth;
    u8 cellHeight;
    u16 cellSize;
    s8 baselinePos;
    u8 maxCharWidth;
    u8 bpp;
    u8 flags;
    u8 glyphTable[];
} NNSG2dFontGlyph;

typedef struct NNSG2dFontInformation {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
    NNSG2dCharWidths defaultWidth;
    u8 encoding;
    NNSG2dFontGlyph *pGlyph;
    void *pWidth;
    void *pMap;
} NNSG2dFontInformation;

typedef u16 (*NNSiG2dSplitCharCallback)(const void **character);

typedef struct NNSG2dFont {
    NNSG2dFontInformation *pRes;
    NNSiG2dSplitCharCallback splitCharacter;
} NNSG2dFont;

typedef struct NNSG2dCharCanvas NNSG2dCharCanvas;

typedef struct NNSiG2dCharCanvasVTable NNSiG2dCharCanvasVTable;

struct NNSG2dCharCanvas {
    u8 *charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    const NNSiG2dCharCanvasVTable *vtable;
};

typedef struct NNSG2dTextCanvas {
    NNSG2dCharCanvas *pCanvas;
    NNSG2dFont *pFont;
    int hSpace;
    int vSpace;
} NNSG2dTextCanvas;

typedef struct NNSiG2dTextDirection {
    s8 x;
    s8 y;
} NNSiG2dTextDirection;

typedef struct NNSG2dTagCallbackInfo {
    NNSG2dTextCanvas txn;
    const void *str;
    int x;
    int y;
    int clr;
    void *cbParam;
} NNSG2dTagCallbackInfo;

typedef void (*NNSG2dTagCallback)(u16 tag, NNSG2dTagCallbackInfo *info);

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

typedef struct NNSG2dCharacterData {
    u16 height;
    u16 width;
    GXTexFmt pixelFmt;
    GXOBJVRamModeChar mappingType;
    u32 characterFmt;
    u32 szByte;
    void *pRawData;
} NNSG2dCharacterData;

typedef struct NNSG2dPaletteData {
    GXTexFmt fmt;
    BOOL extendedPalette;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

#endif
