#ifndef G2D_TEXTCANVAS_INTERNAL_H
#define G2D_TEXTCANVAS_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

#define NULL ((void *)0)

typedef char NNSG2dChar;

typedef struct NNSG2dCharWidths {
    s8 left;
    u8 glyphWidth;
    s8 charWidth;
} NNSG2dCharWidths;

typedef struct NNSG2dFontInformation {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
    NNSG2dCharWidths defaultWidth;
    u8 encoding;
    void *pGlyph;
    void *pWidth;
    void *pMap;
} NNSG2dFontInformation;

typedef u16 (*NNSiG2dSplitCharCallback)(const void **ppChar);

typedef struct NNSG2dFont {
    NNSG2dFontInformation *pRes;
    NNSiG2dSplitCharCallback cbCharSpliter;
} NNSG2dFont;

typedef struct NNSG2dCharCanvas NNSG2dCharCanvas;

typedef struct NNSG2dTextCanvas {
    const NNSG2dCharCanvas *pCanvas;
    const NNSG2dFont *pFont;
    int hSpace;
    int vSpace;
} NNSG2dTextCanvas;

typedef struct NNSG2dTextRect {
    int width;
    int height;
} NNSG2dTextRect;

typedef struct NNSG2dTagCallbackInfo {
    NNSG2dTextCanvas txn;
    const NNSG2dChar *str;
    int x;
    int y;
    int clr;
    void *cbParam;
} NNSG2dTagCallbackInfo;

typedef void (*NNSG2dTagCallback)(u16 c, NNSG2dTagCallbackInfo *pInfo);

typedef struct NNSiG2dTextDirection {
    s8 x;
    s8 y;
} NNSiG2dTextDirection;

enum {
    NNS_G2D_HORIZONTALORIGIN_CENTER = 0x10,
    NNS_G2D_HORIZONTALORIGIN_RIGHT = 0x20,
    NNS_G2D_VERTICALORIGIN_MIDDLE = 0x2,
    NNS_G2D_VERTICALORIGIN_BOTTOM = 0x4,
    NNS_G2D_VERTICALALIGN_MIDDLE = 0x80,
    NNS_G2D_VERTICALALIGN_BOTTOM = 0x100,
    NNS_G2D_HORIZONTALALIGN_CENTER = 0x400,
    NNS_G2D_HORIZONTALALIGN_RIGHT = 0x800
};

extern int NNS_G2dCharCanvasDrawChar(const NNSG2dCharCanvas *pCC,
                                     const NNSG2dFont *pFont,
                                     int x, int y, int cl, u16 ccode);
extern int NNSi_G2dFontGetStringWidth(const NNSG2dFont *pFont, int hSpace,
                                      const void *str, const void **pPos);
extern int NNSi_G2dFontGetTextHeight(const NNSG2dFont *pFont, int vSpace,
                                     const void *txt);
extern NNSG2dTextRect NNSi_G2dFontGetTextRect(const NNSG2dFont *pFont,
                                               int hSpace, int vSpace,
                                               const void *txt);

inline NNSiG2dSplitCharCallback NNSi_G2dFontGetSpliter(const NNSG2dFont *pFont)
{
    return pFont->cbCharSpliter;
}

inline s8 NNS_G2dFontGetLineFeed(const NNSG2dFont *pFont)
{
    return pFont->pRes->linefeed;
}

inline int NNS_G2dTextCanvasGetStringWidth(const NNSG2dTextCanvas *pTxn,
                                                   const void *str,
                                                   const void **pPos)
{
    return NNSi_G2dFontGetStringWidth(pTxn->pFont, pTxn->hSpace, str, pPos);
}

inline int NNS_G2dTextCanvasGetTextHeight(const NNSG2dTextCanvas *pTxn,
                                                  const void *txt)
{
    return NNSi_G2dFontGetTextHeight(pTxn->pFont, pTxn->vSpace, txt);
}

inline NNSG2dTextRect NNS_G2dFontGetTextRect(const NNSG2dFont *pFont,
                                                     int hSpace, int vSpace,
                                                     const NNSG2dChar *txt)
{
    NNSG2dTextRect rect = NNSi_G2dFontGetTextRect(pFont, hSpace, vSpace, txt);
    return rect;
}

inline NNSG2dTextRect NNS_G2dTextCanvasGetTextRect(const NNSG2dTextCanvas *pTxn,
                                                           const NNSG2dChar *txt)
{
    return NNS_G2dFontGetTextRect(pTxn->pFont, pTxn->hSpace, pTxn->vSpace, txt);
}

void NNSi_G2dTextCanvasDrawString(const NNSG2dTextCanvas *pTxn, int x, int y,
                                  int cl, const void *str, const void **pPos,
                                  NNSiG2dTextDirection d);
void NNSi_G2dTextCanvasDrawTextAlign(const NNSG2dTextCanvas *pTxn, int x, int y,
                                     int areaWidth, int cl, u32 flags,
                                     const void *txt, NNSiG2dTextDirection d);

#endif
