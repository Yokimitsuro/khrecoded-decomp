#include "libs/nns/g2d/include/g2d_textcanvas_internal.h"

void NNSi_G2dTextCanvasDrawText(const NNSG2dTextCanvas *pTxn, int x, int y,
                                int cl, u32 flags, const void *txt,
                                NNSiG2dTextDirection d)
{
    NNSG2dTextRect area;

    {
        area = NNS_G2dTextCanvasGetTextRect(pTxn, txt);

        if (flags & NNS_G2D_HORIZONTALORIGIN_CENTER) {
            const int offset = -(area.width + 1) / 2;
            x += offset * d.x;
            y += offset * d.y;
        } else if (flags & NNS_G2D_HORIZONTALORIGIN_RIGHT) {
            const int offset = -area.width;
            x += offset * d.x;
            y += offset * d.y;
        }

        if (flags & NNS_G2D_VERTICALORIGIN_MIDDLE) {
            const int offset = -(area.height + 1) / 2;
            x += offset * -d.y;
            y += offset * d.x;
        } else if (flags & NNS_G2D_VERTICALORIGIN_BOTTOM) {
            const int offset = -area.height;
            x += offset * -d.y;
            y += offset * d.x;
        }
    }

    NNSi_G2dTextCanvasDrawTextAlign(pTxn, x, y, area.width, cl, flags, txt, d);
}
