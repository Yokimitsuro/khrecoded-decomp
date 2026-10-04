#include "libs/nns/g2d/include/g2d_textcanvas_internal.h"

void NNSi_G2dTextCanvasDrawTextRect(const NNSG2dTextCanvas *pTxn, int x, int y,
                                    int w, int h, int cl, u32 flags,
                                    const void *txt, NNSiG2dTextDirection d)
{
    {
        if (flags & NNS_G2D_VERTICALALIGN_BOTTOM) {
            const int height = NNS_G2dTextCanvasGetTextHeight(pTxn, txt);
            const int offset = h - height;
            x += offset * -d.y;
            y += offset * d.x;
        } else if (flags & NNS_G2D_VERTICALALIGN_MIDDLE) {
            const int height = NNS_G2dTextCanvasGetTextHeight(pTxn, txt);
            const int offset = (h + 1) / 2 - (height + 1) / 2;
            x += offset * -d.y;
            y += offset * d.x;
        }
    }

    NNSi_G2dTextCanvasDrawTextAlign(pTxn, x, y, w, cl, flags, txt, d);
}
