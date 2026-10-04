#include "libs/nns/g2d/include/g2d_textcanvas_internal.h"

void NNSi_G2dTextCanvasDrawTextAlign(const NNSG2dTextCanvas *pTxn, int x, int y,
                                     int areaWidth, int cl, u32 flags,
                                     const void *txt, NNSiG2dTextDirection d)
{
    const void *str;
    int linefeed;
    int linefeedx;
    int linefeedy;
    int line;
    int charSpace;
    const NNSG2dFont *pFont;
    int px, py;

    charSpace = pTxn->hSpace;
    linefeed = NNS_G2dFontGetLineFeed(pTxn->pFont) + pTxn->vSpace;
    pFont = pTxn->pFont;
    str = txt;
    linefeedx = linefeed * -d.y;
    linefeedy = linefeed * d.x;
    line = 0;

    while (str != NULL) {
        px = x + line * linefeedx;
        py = y + line * linefeedy;

        if (flags & NNS_G2D_HORIZONTALALIGN_RIGHT) {
            const int width = NNS_G2dTextCanvasGetStringWidth(pTxn, str, NULL);
            const int offset = areaWidth - width;
            px += offset * d.x;
            py += offset * d.y;
        } else if (flags & NNS_G2D_HORIZONTALALIGN_CENTER) {
            const int width = NNS_G2dTextCanvasGetStringWidth(pTxn, str, NULL);
            const int offset = (areaWidth + 1) / 2 - (width + 1) / 2;
            px += offset * d.x;
            py += offset * d.y;
        }

        NNSi_G2dTextCanvasDrawString(pTxn, px, py, cl, str, &str, d);
        line++;
    }
}
