#include "libs/nns/g2d/include/g2d_textcanvas_internal.h"

void NNSi_G2dTextCanvasDrawString(const NNSG2dTextCanvas *pTxn, int x, int y,
                                  int cl, const void *str, const void **pPos,
                                  NNSiG2dTextDirection d)
{
    const void *pos;
    int charSpace;
    const NNSG2dFont *pFont;
    u16 c;
    NNSiG2dSplitCharCallback getNextChar;

    charSpace = pTxn->hSpace;
    pFont = pTxn->pFont;
    pos = str;
    getNextChar = NNSi_G2dFontGetSpliter(pFont);

    while ((c = getNextChar((const void **)&pos)) != 0) {
        if (c == '\n') {
            break;
        }

        {
            const int w = NNS_G2dCharCanvasDrawChar(pTxn->pCanvas, pFont,
                                                    x, y, cl, c) + charSpace;
            x += w * d.x;
            y += w * d.y;
        }
    }

    if (pPos != NULL) {
        *pPos = (c == '\n') ? pos : NULL;
    }
}
