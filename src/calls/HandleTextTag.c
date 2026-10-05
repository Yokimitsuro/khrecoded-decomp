#include "nitro/types.h"
#include "nnsys/g2d.h"

extern int GetLineWidth(const NNSG2dTextCanvas *canvas, const u16 *text, const u16 **nextLine);

void HandleTextTag(int tag, NNSG2dTagCallbackInfo *info)
{
    int *colors = (int *)info->cbParam;

    switch (tag) {
    case 1:
    case 2:
        info->clr = (u8)colors[tag - 1];
        break;
    case 4:
        info->clr = (u8)(colors[0] >> 8);
        break;
    case 0x1f: {
        int areaWidth = info->txn.pCanvas->areaWidth * 8;
        int width = GetLineWidth(&info->txn, (const u16 *)info->str, NULL);

        info->x = (areaWidth + 1) / 2 - (width + 1) / 2;
        info->y += info->txn.vSpace + info->txn.pFont->pRes->linefeed;
        break;
    }
    }
}
