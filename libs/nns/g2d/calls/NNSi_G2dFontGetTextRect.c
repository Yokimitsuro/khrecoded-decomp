typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;

#define NULL ((void *)0)

typedef struct NNSG2dCharWidths { s8 left; u8 glyphWidth; s8 charWidth; } NNSG2dCharWidths;
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
typedef struct NNSG2dFont { NNSG2dFontInformation *pRes; void *cbCharSpliter; } NNSG2dFont;
typedef struct NNSG2dTextRect { int width; int height; } NNSG2dTextRect;

extern int NNSi_G2dFontGetStringWidth(const NNSG2dFont *pFont, int hSpace, const void *str, const void **pPos);

inline s8 NNS_G2dFontGetLineFeed(const NNSG2dFont *pFont)
{
    return pFont->pRes->linefeed;
}

NNSG2dTextRect NNSi_G2dFontGetTextRect(const NNSG2dFont *pFont, int hSpace, int vSpace, const void *txt)
{
    int lines = 1;
    NNSG2dTextRect rect = {0, 0};
    while (txt != NULL) {
        const int width = NNSi_G2dFontGetStringWidth(pFont, hSpace, txt, &txt);
        if (width > rect.width) {
            rect.width = width;
        }
        lines++;
    }
    rect.height = ((lines - 1) * (NNS_G2dFontGetLineFeed(pFont) + vSpace) - vSpace);
    return rect;
}
