#include "nitro/types.h"
#include "nnsys/g2d.h"

extern u16 NNS_G2dFontFindGlyphIndex(const NNSG2dFont *font, u16 c);
extern const NNSG2dCharWidths *NNS_G2dFontGetCharWidthsFromIndex(const NNSG2dFont *font, u16 index);

int GetLineWidth(const NNSG2dTextCanvas *canvas, const u16 *text, const u16 **nextLine)
{
    const NNSG2dFont *font = canvas->pFont;
    int hSpace = canvas->hSpace;
    int width = 0;
    int result;
    u16 c;

    while ((c = *text) != 0 && c != '\n' && c != 0x1f) {
        if (c >= 0x20) {
            u16 index = NNS_G2dFontFindGlyphIndex(font, c);
            if (index == NNS_G2D_GLYPH_INDEX_NOT_FOUND) {
                index = font->pRes->alterCharIndex;
            }
            width += hSpace + NNS_G2dFontGetCharWidthsFromIndex(font, index)->charWidth;
        }
        text++;
    }
    result = width - hSpace;
    if (result <= 0) {
        result = 0;
    }
    if (nextLine != NULL) {
        if (c == '\n') {
            *nextLine = text + 1;
            return result;
        }
        *nextLine = NULL;
    }
    return result;
}
