typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;

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
typedef struct NNSG2dTextRect { int width; int height; } NNSG2dTextRect;

inline NNSiG2dSplitCharCallback NNSi_G2dFontGetSpliter(const NNSG2dFont *pFont)
{
    return pFont->cbCharSpliter;
}

inline s8 NNS_G2dFontGetLineFeed(const NNSG2dFont *pFont)
{
    return pFont->pRes->linefeed;
}

int NNSi_G2dFontGetTextHeight(const NNSG2dFont *pFont, int vSpace, const void *txt)
{
    const void *pos = txt;
    int lines = 1;
    NNSG2dTextRect rect = {0, 0};
    u16 c;
    NNSiG2dSplitCharCallback getNextChar;

    getNextChar = NNSi_G2dFontGetSpliter(pFont);

    while ((c = getNextChar((const void **)&pos)) != 0) {
        if (c == '\n') {
            lines++;
        }
    }

    return lines * (NNS_G2dFontGetLineFeed(pFont) + vSpace) - vSpace;
}
