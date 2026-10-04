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
typedef u16 (*NNSiG2dSplitCharCallback)(const void **ppChar);
typedef struct NNSG2dFont { NNSG2dFontInformation *pRes; NNSiG2dSplitCharCallback cbCharSpliter; } NNSG2dFont;

extern u16 NNS_G2dFontFindGlyphIndex(const NNSG2dFont *pFont, u16 c);
extern const NNSG2dCharWidths *NNS_G2dFontGetCharWidthsFromIndex(const NNSG2dFont *pFont, u16 idx);

inline NNSiG2dSplitCharCallback NNSi_G2dFontGetSpliter(const NNSG2dFont *pFont)
{
    return pFont->cbCharSpliter;
}

inline u16 NNS_G2dFontGetGlyphIndex(const NNSG2dFont *pFont, u16 c)
{
    const u16 idx = NNS_G2dFontFindGlyphIndex(pFont, c);
    return idx != 0xffff ? idx : pFont->pRes->alterCharIndex;
}

inline const NNSG2dCharWidths *NNS_G2dFontGetCharWidths(const NNSG2dFont *pFont, u16 c)
{
    u16 iGlyph;
    iGlyph = NNS_G2dFontGetGlyphIndex(pFont, c);
    return NNS_G2dFontGetCharWidthsFromIndex(pFont, iGlyph);
}

inline int NNS_G2dFontGetCharWidth(const NNSG2dFont *pFont, u16 c)
{
    const NNSG2dCharWidths *pWidths;
    pWidths = NNS_G2dFontGetCharWidths(pFont, c);
    return pWidths->charWidth;
}

int NNSi_G2dFontGetStringWidth(const NNSG2dFont *pFont, int hSpace, const void *str, const void **pPos)
{
    int width = 0;
    const void *pos = str;
    u16 c;
    NNSiG2dSplitCharCallback getNextChar;

    getNextChar = NNSi_G2dFontGetSpliter(pFont);
    while ((c = getNextChar(&pos)) != 0) {
        u16 idx;
        const NNSG2dCharWidths *pWidths;

        if (c == '\n') {
            break;
        }

        idx = NNS_G2dFontFindGlyphIndex(pFont, c);
        if (idx == 0xffff) {
            idx = pFont->pRes->alterCharIndex;
        }
        pWidths = NNS_G2dFontGetCharWidthsFromIndex(pFont, idx);
        width += hSpace + pWidths->charWidth;
    }
    if (pPos != NULL) {
        *pPos = (c == '\n') ? pos : NULL;
    }
    if (width > 0) {
        width -= hSpace;
    }
    return width;
}
