typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;

#define NULL ((void *)0)

typedef struct NNSG2dCharWidths { s8 left; u8 glyphWidth; s8 charWidth; } NNSG2dCharWidths;
typedef struct NNSG2dFontWidth {
    u16 indexBegin;
    u16 indexEnd;
    struct NNSG2dFontWidth *pNext;
    NNSG2dCharWidths widthTable[];
} NNSG2dFontWidth;
typedef struct NNSG2dFontInformation {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
    NNSG2dCharWidths defaultWidth;
    u8 encoding;
    void *pGlyph;
    NNSG2dFontWidth *pWidth;
    void *pMap;
} NNSG2dFontInformation;
typedef struct NNSG2dFont { NNSG2dFontInformation *pRes; void *cbCharSpliter; } NNSG2dFont;

static inline const NNSG2dCharWidths *GetCharWidthsFromIndex(const NNSG2dFontWidth *pWidth, int idx)
{
    return (NNSG2dCharWidths *)pWidth->widthTable + (idx - pWidth->indexBegin);
}

const NNSG2dCharWidths *NNS_G2dFontGetCharWidthsFromIndex(const NNSG2dFont *pFont, u16 idx)
{
    const NNSG2dFontWidth *pWidth = pFont->pRes->pWidth;
    while (pWidth != NULL) {
        if (pWidth->indexBegin <= idx && idx <= pWidth->indexEnd) {
            return GetCharWidthsFromIndex(pWidth, idx);
        }
        pWidth = pWidth->pNext;
    }
    return &pFont->pRes->defaultWidth;
}
