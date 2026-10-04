#include "libs/nns/g2d/include/g2d_textcanvas_internal.h"

void NNSi_G2dTextCanvasDrawTaggedText(const NNSG2dTextCanvas *pTxn,
                                      int x, int y, int cl, const void *txt,
                                      NNSG2dTagCallback cbFunc, void *cbParam,
                                      NNSiG2dTextDirection d)
{
    const void *pos;
    int linefeed;
    int charSpace;
    const NNSG2dFont *pFont;
    NNSG2dTagCallbackInfo cbInfo;
    u16 c;
    NNSiG2dSplitCharCallback getNextChar;

    int px = x;
    int py = y;

    cbInfo.txn = *pTxn;
    cbInfo.cbParam = cbParam;

    charSpace = cbInfo.txn.hSpace;
    pFont = cbInfo.txn.pFont;
    linefeed = NNS_G2dFontGetLineFeed(pFont) + cbInfo.txn.vSpace;
    pos = txt;
    getNextChar = NNSi_G2dFontGetSpliter(pFont);

    linefeed *= (d.x != 0) ? d.x : -d.y;

    while ((c = getNextChar((const void **)&pos)) != 0) {
        if (c < ' ') {
            if (c == '\n') {
                if (d.x == 0) {
                    px += linefeed;
                    py = y;
                } else {
                    px = x;
                    py += linefeed;
                }
            } else {
                cbInfo.str = (const NNSG2dChar *)pos;
                cbInfo.x = px;
                cbInfo.y = py;
                cbInfo.clr = cl;

                cbFunc(c, &cbInfo);

                pos = (const void *)cbInfo.str;
                px = cbInfo.x;
                py = cbInfo.y;
                cl = cbInfo.clr;

                pFont = cbInfo.txn.pFont;
                charSpace = cbInfo.txn.hSpace;
                linefeed = NNS_G2dFontGetLineFeed(pFont) + cbInfo.txn.vSpace;
                linefeed *= (d.x != 0) ? d.x : -d.y;
            }

            continue;
        } else {
            const int w = NNS_G2dCharCanvasDrawChar(cbInfo.txn.pCanvas,
                                                    cbInfo.txn.pFont,
                                                    px, py, cl, c) + charSpace;
            px += w * d.x;
            py += w * d.y;
        }
    }
}
